#include "net/ip/uip.h"
#include "net/ipv6/uip-ds6.h"
#include <string.h>

#define UIP_IP_BUF        ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

void set_prefix_64(uip_ipaddr_t *); 

static void
init(void)
{
  printf("eth-bridge: INIT\n");
  //slip_set_input_callback(slip_input_callback);
  init_xyz();
}
/*---------------------------------------------------------------------------*/
static int
output()
{
  printf("eth-bridge len=%d\n", uip_len);
  printf("eth-bridge:\n");
  PRINTF("eth-bridge: Destination off-link but no route src=");
  PRINT6ADDR(&UIP_IP_BUF->srcipaddr);
  PRINTF(" dst=");
  PRINT6ADDR(&UIP_IP_BUF->destipaddr);
  PRINTF("\n");
  //output_xyz(packet, len);
  uip_buf[0] = 0xAA;
  uip_buf[1] = 0xCD;
  output_xyz(&uip_buf[20], 64);
  return 0;
}
/*---------------------------------------------------------------------------*/
const struct uip_fallback_interface rpl_interface = {
  init, output
};
/*---------------------------------------------------------------------------*/
