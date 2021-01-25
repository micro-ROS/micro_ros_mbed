#include "mbed.h"

// --- micro-ROS Timing ---
extern "C" int clock_gettime(clockid_t unused, struct timespec *tp)
{
    (void)unused;
    struct timeval tv;
    gettimeofday(&tv, 0);
    tp->tv_sec = tv.tv_sec;
    tp->tv_nsec = tv.tv_usec * 1000;
    return 0;
}

// --- micro-ROS Transports ---
static UnbufferedSerial serial_port(USBTX, USBRX);
Timer t;

#define UART_DMA_BUFFER_SIZE 2048

static uint8_t dma_buffer[UART_DMA_BUFFER_SIZE];
static size_t dma_head = 0, dma_tail = 0;

void on_rx_interrupt()
{
    if (serial_port.read(&dma_buffer[dma_tail], 1)) {
        dma_tail = (dma_tail + 1) % UART_DMA_BUFFER_SIZE;
        if (dma_tail == dma_head) {
            dma_head = (dma_head + 1) % UART_DMA_BUFFER_SIZE;
        }
    }
}

extern "C" bool mbed_serial_open(struct uxrCustomTransport * transport){
    serial_port.baud(115200);
    serial_port.format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
    serial_port.attach(&on_rx_interrupt, SerialBase::RxIrq);

    return true;
}

extern "C" bool mbed_serial_close(struct uxrCustomTransport * transport){
    return (serial_port.close() == 0 ? true : false);
}

extern "C" size_t mbed_serial_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err){
    ssize_t wrote = serial_port.write(buf, len);
    serial_port.sync();
    return (wrote >= 0) ? wrote : 0;
}

extern "C" size_t mbed_serial_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err){
    t.start();
    std::chrono::microseconds elapsed = std::chrono::microseconds(0); 
    std::chrono::microseconds timeout_us = std::chrono::microseconds(timeout*1000);

    size_t wrote = 0;
    while(elapsed < timeout_us && wrote < len){
        if (dma_head != dma_tail){
            buf[wrote] = dma_buffer[dma_head];
            dma_head = (dma_head + 1) % UART_DMA_BUFFER_SIZE;
            wrote++;
        }  
        elapsed = t.elapsed_time();
    }

    return wrote;
}