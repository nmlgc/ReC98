static const int HELP_LINES = 9;

shiftjis_t* BGM_HELP[HELP_LINES] = {
	"ステレオＦＭ音源：PC-9801-86(互換)ボード　　　",
	"　　　　　　　　　CanBe内蔵音源など、         ",
	"　　　　　　　ＦＭ６音＋ＳＳＧ３音＋リズム音源",
	"　標準ＦＭ音源：  PC-9801-26K(互換)ボード     ",
	"                  PC-9801DA等に内蔵の音源など ",
	"　　　　　　　　　ＦＭ３音＋ＳＳＧ３音        ",
	"　　音楽無し：　　ＦＭ音源が無い場合          ",
	"                                              ",
	"なお、これらの設定はＯｐｔｉｏｎで変更可能です",
};

shiftjis_t* SE_HELP[HELP_LINES] = {
	"　ＦＭ音源　：効果音にＦＭ音源を使用します　　",
	"　　　　　　　ＢＧＭがステレオＦＭ音源時推奨　",
	"　 　 　　（標準ＦＭ音源では、3chを使用します ",
	"　 　　　　 ので、ＢＧＭが正常にきけないかも）",
	"Ｂｅｅｐ音源：効果音にＢｅｅｐ音源を使用します",
	"              ＦＭ音源が無い場合使用します　　",
	" 効果音無し ：何らかの事情で効果音を鳴らしたく",
	"　　　　　　　無い場合                        ",
	"なお、これらの設定はＯｐｔｉｏｎで変更可能です",
};

#define BGM_CHOICE_FM86	"ステレオＦＭ音源"
#define BGM_CHOICE_FM26	"　標準ＦＭ音源　"
#define BGM_CHOICE_OFF 	"　　音楽無し　　"

#define SE_CHOICE_FM  	"　　ＦＭ音源　　"
#define SE_CHOICE_BEEP	"　Ｂｅｅｐ音源　"
#define SE_CHOICE_OFF 	"　 効果音無し 　\0" SETUP_BGM_CAPTION

#define SETUP_BGM_CAPTION	"　　　　　使用する音源を選択して下さいね☆"
