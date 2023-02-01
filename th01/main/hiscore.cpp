void scoredat_load_hiscore(void)
{
	scoredat_load();
	resident->hiscore = scoredat_hiscore_get();
	scoredat_free();
}
