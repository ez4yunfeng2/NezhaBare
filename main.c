#define SUNXI_UART_THR     0
#define SUNXI_UART_RBR     0
#define SUNXI_UART_USR     0x1F //addr:0x7C
#define SUNXI_UART_USR_NF  0x02
#define SUNXI_UART_USR_RFNE  0x04
static volatile unsigned int* sunxi_uart = (void *)0x02500000;

#define LOGO \
".______       __    __      _______.___________.  _______..______   __\n\r"\
"|   _  \\     |  |  |  |    /       |           | /       ||   _  \\ |  |\n\r"\
"|  |_)  |    |  |  |  |   |   (----`---|  |----`|   (----`|  |_)  ||  |\n\r" \
"|      /     |  |  |  |    \\   \\       |  |      \\   \\    |   _  < |  |\n\r"\
"|  |\\  \\----.|  `--'  |.----)   |      |  |  .----)   |   |  |_)  ||  | \n\r"\
"| _| `._____| \\______/ |_______/       |__|  |_______/    |______/ |__| \n\r"

void sunxi_uart_putc(char ch)
{
	while ((sunxi_uart[SUNXI_UART_USR] & SUNXI_UART_USR_NF) == 0);
	sunxi_uart[SUNXI_UART_THR] = ch;
}

int sunxi_uart_getc(void)
{
	if ((sunxi_uart[SUNXI_UART_USR] & SUNXI_UART_USR_RFNE) != 0)
		return sunxi_uart[SUNXI_UART_RBR];
	else
		return -1;
}
int getchar(void){
	int ch;
	while ( (ch = sunxi_uart_getc()) == -1 );

	return ch;
}

int _init()
{
	int i;
	for(i=0;LOGO[i]!=0;i++){
		sunxi_uart_putc(LOGO[i]);
	}
    char *msg = "Hello NeZha\n\r";
    for(i=0;msg[i]!=0;i++){
		sunxi_uart_putc(msg[i]);
	}
	while(1);
}
