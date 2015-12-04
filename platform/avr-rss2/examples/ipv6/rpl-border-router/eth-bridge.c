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

}
/*---------------------------------------------------------------------------*/
static int
output(void)
{
  PRINTF("eth-bridge: Destination off-link but no route src=");
  PRINT6ADDR(&UIP_IP_BUF->srcipaddr);
  PRINTF(" dst=");
  PRINT6ADDR(&UIP_IP_BUF->destipaddr);
  PRINTF("\n");
  return 0;
}
/*---------------------------------------------------------------------------*/
const struct uip_fallback_interface rpl_interface = {
  init, output
};
/*---------------------------------------------------------------------------*/
