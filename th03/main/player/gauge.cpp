#include "th03/main/player/gauge.hpp"
#include "th03/main/player/stuff.hpp"

void pascal near gauge_avail_add(pid_t pid, uint8_t charge)
{
	player_stuff_t near& p = players[pid];
	if(p.hyper_active || (p.gauge_avail >= GAUGE_MAX)) {
		return;
	}
	p.gauge_avail += charge;
	if(p.gauge_avail > GAUGE_MAX) {
		p.gauge_avail = GAUGE_MAX;
	}
}
