#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_H_

typedef enum
{
	MENUOPTION_CONTINUE = 0,
	MENUOPTION_RETRY,
	MENUOPTION_QUIT,
	MENUOPTION_MAX
}MENUOPTION;

//プロトタイプ宣言
void InitPauseMenu(void);
void UninitPauseMenu(void);
void UpdatePauseMenu(void);
void DrawPauseMenu(void);
void SetPauseMenu(void);
bool GetPauseMenu(void);

#endif _PAUSEMENU_H_