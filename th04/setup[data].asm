SETUP_BGM_HELP	dd aSETUP_BGM_HELP1
		dd aSETUP_BGM_HELP2
		dd aSETUP_BGM_HELP3
		dd aSETUP_BGM_HELP4
		dd aSETUP_BGM_HELP5
		dd aSETUP_BGM_HELP6
		dd aSETUP_BGM_HELP7
		dd aSETUP_BGM_HELP8
		dd aSETUP_TAIL
SETUP_SE_HELP	dd aSETUP_SE_HELP1
		dd aSETUP_SE_HELP2
		dd aSETUP_SE_HELP3
		dd aSETUP_SE_HELP4
		dd aSETUP_SE_HELP5
		dd aSETUP_SE_HELP6
		dd aSETUP_SE_HELP7
		dd aSETUP_SE_HELP8
		dd aSETUP_TAIL
aSETUP_BGM_HELP1 db 'ステレオＦＭ音源：PC-9801-86(互換)ボード　　　',0
aSETUP_BGM_HELP2 db '　　　　　　　　　CanBe内蔵音源など、         ',0
aSETUP_BGM_HELP3 db '　　　　　　　ＦＭ６音＋ＳＳＧ３音＋リズム音源',0
aSETUP_BGM_HELP4 db '　標準ＦＭ音源：  PC-9801-26K(互換)ボード     ',0
aSETUP_BGM_HELP5 db '                  PC-9801DA等に内蔵の音源など ',0
aSETUP_BGM_HELP6 db '　　　　　　　　　ＦＭ３音＋ＳＳＧ３音        ',0
aSETUP_BGM_HELP7 db '　　音楽無し：　　ＦＭ音源が無い場合          ',0
aSETUP_BGM_HELP8 db '                                              ',0
aSETUP_TAIL	db 'なお、これらの設定はＯｐｔｉｏｎで変更可能です',0
aSETUP_SE_HELP1 db '　ＦＭ音源　：効果音にＦＭ音源を使用します　　',0
aSETUP_SE_HELP2 db '　　　　　　　ＢＧＭがステレオＦＭ音源時推奨　',0
aSETUP_SE_HELP3 db '　 　 　　（標準ＦＭ音源では、3chを使用します ',0
aSETUP_SE_HELP4 db '　 　　　　 ので、ＢＧＭが正常にきけないかも）',0
aSETUP_SE_HELP5 db 'Ｂｅｅｐ音源：効果音にＢｅｅｐ音源を使用します',0
aSETUP_SE_HELP6 db '              ＦＭ音源が無い場合使用します　　',0
aSETUP_SE_HELP7 db ' 効果音無し ：何らかの事情で効果音を鳴らしたく',0
aSETUP_SE_HELP8 db '　　　　　　　無い場合                        ',0
aSETUP_BGM_OPTION1 db 'ステレオＦＭ音源',0
aSETUP_BGM_OPTION2 db '　標準ＦＭ音源　',0
aSETUP_BGM_OPTION3 db '　　音楽無し　　',0
aSETUP_SE_OPTION1 db '　　ＦＭ音源　　',0
aSETUP_SE_OPTION2 db '　Ｂｅｅｐ音源　',0
aSETUP_SE_OPTION3 db '　 効果音無し 　',0
aSETUP_BGM_HEAD	db '　　　　　使用する音源を選択して下さいね☆',0
aSETUP_SE_HEAD	db '　　　　効果音に使用する音源を選択してね☆',0
aMswin_bft	db 'mswin.bft',0
aMs_pi		db 'ms.pi',0
	even
