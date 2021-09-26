void cards_hittest(int stage_num)
{
	extern unsigned char card_flip_cycle;

	for(unsigned int i = 0; i < cards.count; i++) {
		struct {
			upixel_t y, x;
		} delta;

		delta.x = ((cards.left[i] - orb_cur_left) < 0)
			? ((cards.left[i] - orb_cur_left) * -1)
			: (cards.left[i] - orb_cur_left);

		delta.y = ((cards.top[i] - orb_cur_top) < 0)
			? ((cards.top[i] - orb_cur_top) * -1)
			: (cards.top[i] - orb_cur_top);

		if((
			(delta.x < (ORB_W - (ORB_W / 4))) &&
			(delta.y < (ORB_H - (ORB_H / 4))) &&
			(cards.flag[i] == CARD_ALIVE)
		) || (
			(test_damage == true) && (cards.flag[i] == CARD_ALIVE)
		) || (
			(bomb_damaging == true) &&
			((bomb_frames % cards.count) == i) &&
			((rand() % 4) != 0) &&
			(cards.flag[i] == CARD_ALIVE)
		)) {
			cards.flag[i] = CARD_FLIPPING;
			cards_score[i] = ((((stage_num / 5) * 100) + 100) + (
				static_cast<unsigned long>(cardcombo_cur * cardcombo_cur) *
				(((rank == RANK_LUNATIC) * 15) + 20)
			));
			if(cards_score[i] > CARD_SCORE_CAP) {
				cards_score[i] = CARD_SCORE_CAP;
			}
			score += cards_score[i];
			cardcombo_cur++;
			if(cardcombo_max < cardcombo_cur) {
				cardcombo_max = cardcombo_cur;
			}
			hud_score_and_cardcombo_render();

			if(((card_flip_cycle++) % 10) == 0) {
				if(card_flip_cycle >= 140) {
					card_flip_cycle = 1;
					if(bomb_damaging) {
add_point_item:
						items_point_add(i);
					} else {
						items_bomb_add(i);
					}
				} else {
					goto add_point_item;
				}
			}
			mdrv2_se_play(2);
		}
	}
}
