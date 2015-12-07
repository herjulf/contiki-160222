#include "net/ip/uip.h"
#include "net/ipv6/uip-ds6.h"
#include <string.h>
#include "ip64-eth-interface.h"

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
  ip64_eth_addr_set(&linkaddr_node_addr);
  ip64_init();
  ip64_eth_interface.init();
}
/*---------------------------------------------------------------------------*/
static int
output()
{
  printf("eth-bridge:\n");
  PRINTF("eth-bridge: Destination off-link but no route src=");
  PRINT6ADDR(&UIP_IP_BUF->srcipaddr);
  PRINTF(" dst=");
  PRINT6ADDR(&UIP_IP_BUF->destipaddr);
  PRINTF("\n");
  ip64_eth_interface.output();
  return 0;
}
/*---------------------------------------------------------------------------*/
const struct uip_fallback_interface rpl_interface = {
  init, output
};
/*---------------------------------------------------------------------------*/
