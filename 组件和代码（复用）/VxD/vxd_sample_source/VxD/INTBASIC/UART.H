#define UART_REG_THR          0x00
#define UART_REG_RDR          0x00
#define UART_REG_IER          0x01
#define UART_REG_IIR          0x02
#define UART_REG_LCR          0x03
#define UART_REG_MCR          0x04
#define UART_REG_LSR          0x05
#define UART_REG_BAUDLO       0x00
#define UART_REG_BAUDHI       0x01

#define UART_IIR_NONE         0x01
#define UART_IIR_THRE         0x02
#define UART_IIR_RXRDY        0x04
#define UART_IER_THRE         0x02
#define UART_IER_RXRDY        0x01
#define UART_MCR_OUT2         0x08
#define UART_MCR_LOOP         0x10
#define UART_LSR_THRE         0x20
#define UART_LCR_DLAB         0x80
#define UART_LCR_8N1          0x03
#define UART_LSR_RXRDY        0x01
#define BAUD_1200             0x60
#define BAUD_110              0x0417L 


