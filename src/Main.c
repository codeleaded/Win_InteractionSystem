// #include "C:/Wichtig/System/Static/Library/WindowEngine1.0.h"
// #include "C:/Wichtig/System/Static/Library/Victor2.h"
// #include "C:/Wichtig/System/Static/Library/Vdctor2.h"
// #include "C:/Wichtig/System/Static/Library/Complex.h"
// #include "C:/Wichtig/System/Static/Library/TransformedView.h"
// #include "C:\Wichtig\System\Static\Container\Vector.h"

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/InteractionSystem.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"

InteractionSystem menu;
InteractionOption* selected;

TransformedView tv;
Rect rect;
Vec2 velocity;
Vec2 acceleration;

void Setup(AlxWindow* w){
	menu = InteractionSystem_New(
		"./assets/FoldUp.png",
		"./assets/FoldDown.png",
		"./assets/Rainbow_Atlas.png",
		64
	);

	InteractionSystem_Set(&menu,0,(int[]){   },
		InteractionOption_Make(
			TheaterOption_New(0,"David",NULL),
			MenuSystem_Make(
				"./assets/Pointer.png",
				"./assets/Fold.png",
				"./assets/FoldUp.png",
				"./assets/FoldDown.png",
				"./assets/Rainbow_Atlas.png",64,0.5f,
				MenuOption_Make(0,"NONE",NULL,NULL,NULL,3,2),
				(Branch*[]){
					Branch_New((MenuOption[]){ MenuOption_New(0,"Yes",NULL,NULL,NULL) },sizeof(MenuOption)),
					Branch_New((MenuOption[]){ MenuOption_New(0,"No",NULL,NULL,NULL) },sizeof(MenuOption)),
					NULL
				}
			),
			"Are you dumb? What do you choose?...",
			0.5f
		)
	);
	InteractionSystem_Add(&menu,0,(int[]){   },
		InteractionOption_Make(
			TheaterOption_New(0,"David",NULL),
			MenuSystem_Make(
				"./assets/Pointer.png",
				"./assets/Fold.png",
				"./assets/FoldUp.png",
				"./assets/FoldDown.png",
				"./assets/Rainbow_Atlas.png",64,0.5f,
				MenuOption_Make(0,"NONE",NULL,NULL,NULL,3,2),
				(Branch*[]){
					Branch_New((MenuOption[]){ MenuOption_New(0,"Yes",NULL,NULL,NULL) },sizeof(MenuOption)),
					Branch_New((MenuOption[]){ MenuOption_New(0,"No",NULL,NULL,NULL) },sizeof(MenuOption)),
					NULL
				}
			),
			"Wtf! You are dumb?",
			0.5f
		)
	);
	InteractionSystem_Add(&menu,1,(int[]){ 0 },
		InteractionOption_Make(
			TheaterOption_New(0,"David",NULL),
			MenuSystem_Make(
				"./assets/Pointer.png",
				"./assets/Fold.png",
				"./assets/FoldUp.png",
				"./assets/FoldDown.png",
				"./assets/Rainbow_Atlas.png",64,0.5f,
				MenuOption_New(0,NULL,NULL,NULL,NULL),
				(Branch*[]){
					NULL
				}
			),
			"You are dumb!",
			0.5f
		)
	);
	InteractionSystem_Add(&menu,1,(int[]){ 0 },
		InteractionOption_Make(
			TheaterOption_New(0,"David",NULL),
			MenuSystem_Make(
				"./assets/Pointer.png",
				"./assets/Fold.png",
				"./assets/FoldUp.png",
				"./assets/FoldDown.png",
				"./assets/Rainbow_Atlas.png",64,0.5f,
				MenuOption_New(0,NULL,NULL,NULL,NULL),
				(Branch*[]){
					NULL
				}
			),
			"You are not dumb!",
			0.5f
		)
	);

	InteractionSystem_Add(&menu,0,(int[]){   },
		InteractionOption_Make(
			TheaterOption_New(0,"David",NULL),
			MenuSystem_Make(
				"./assets/Pointer.png",
				"./assets/Fold.png",
				"./assets/FoldUp.png",
				"./assets/FoldDown.png",
				"./assets/Rainbow_Atlas.png",64,0.5f,
				MenuOption_Make(0,"NONE",NULL,NULL,NULL,3,2),
				(Branch*[]){
					Branch_New((MenuOption[]){ MenuOption_New(0,"Yes",NULL,NULL,NULL) },sizeof(MenuOption)),
					Branch_New((MenuOption[]){ MenuOption_New(0,"No",NULL,NULL,NULL) },sizeof(MenuOption)),
					NULL
				}
			),
			"Are you sure that you are not dumb?",
			0.5f
		)
	);
	InteractionSystem_Add(&menu,1,(int[]){ 1 },
		InteractionOption_Make(
			TheaterOption_New(0,"David",NULL),
			MenuSystem_Make(
				"./assets/Pointer.png",
				"./assets/Fold.png",
				"./assets/FoldUp.png",
				"./assets/FoldDown.png",
				"./assets/Rainbow_Atlas.png",64,0.5f,
				MenuOption_New(0,NULL,NULL,NULL,NULL),
				(Branch*[]){
					NULL
				}
			),
			"You are really dumb!",
			0.5f
		)
	);
	InteractionSystem_Add(&menu,1,(int[]){ 1 },
		InteractionOption_Make(
			TheaterOption_New(0,"David",NULL),
			MenuSystem_Make(
				"./assets/Pointer.png",
				"./assets/Fold.png",
				"./assets/FoldUp.png",
				"./assets/FoldDown.png",
				"./assets/Rainbow_Atlas.png",64,0.5f,
				MenuOption_New(0,NULL,NULL,NULL,NULL),
				(Branch*[]){
					NULL
				}
			),
			"You are really not dumb!",
			0.5f
		)
	);


	tv = TransformedView_New((Vec2){ GetWidth(),GetHeight() });
	TransformedView_Offset(&tv,(Vec2){ 0.0f,0.0f });

	rect = (Rect){ 0.0f,0.0f,0.05f,0.05f };
	velocity = (Vec2){ 0.0f,0.0f };
	acceleration = (Vec2){ 0.0f,0.0f };
}
void Update(AlxWindow* w){
	tv.ZoomSpeed = (float)w->ElapsedTime;
	TransformedView_HandlePanZoom(&tv,window.Strokes,(Vec2){ GetMouse().x,GetMouse().y });
	
	if(Stroke(ALX_KEY_ENTER).PRESSED){
		Branch* b = Tree_Get_Branch(&menu.theater,menu.trace.size,menu.trace.Memory);
		InteractionOption* mo = (InteractionOption*)b->Memory;
		MenuOption* select = MenuSystem_Select(&mo->selections);
		
		if(CStr_Cmp(select->text,"Yes")){
			TheaterSystem_Right(&menu,0);
		}else if(CStr_Cmp(select->text,"No")){
			TheaterSystem_Right(&menu,1);
		}else{
			menu.visible = 0;
		}
	}
	
	if(Stroke(ALX_KEY_UP).PRESSED){
		TheaterSystem_Up(&menu);
	}
	if(Stroke(ALX_KEY_DOWN).PRESSED){
		TheaterSystem_Down(&menu);
	}
	if(Stroke(ALX_KEY_LEFT).PRESSED){
		TheaterSystem_Left(&menu);
	}
	if(Stroke(ALX_KEY_RIGHT).PRESSED){
		TheaterSystem_Right(&menu,0);
	}

	if(Stroke(ALX_KEY_W).PRESSED){
		InteractionSystem_Up(&menu);
	}
	if(Stroke(ALX_KEY_S).PRESSED){
		InteractionSystem_Down(&menu);
	}

	InteractionSystem_Update(&menu,(float)w->ElapsedTime);


	velocity = Vec2_Add(velocity,Vec2_Mulf(acceleration,w->ElapsedTime));
	rect.p = Vec2_Add(rect.p,Vec2_Mulf(velocity,w->ElapsedTime));

	if(rect.p.x<0.0f){
		rect.p.x = 0.0f;
		velocity.x *= -1.0f;
	}
	if(rect.p.y<0.0f){
		rect.p.y = 0.0f;
		velocity.y *= -1.0f;
	}
	if(rect.p.x>1.0f - rect.d.x){
		rect.p.x = 1.0f - rect.d.x;
		velocity.x *= -1.0f;
	}
	if(rect.p.y>1.0f - rect.d.y){
		rect.p.y = 1.0f - rect.d.y;
		velocity.y *= -1.0f;
	}



	Clear(WHITE);
	

	Vec2 bg_p = TransformedView_WorldScreenPos(&tv,(Vec2){ 0.0f,0.0f });
	Vec2 bg_d = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });
	RenderRect(bg_p.x,bg_p.y,bg_d.x,bg_d.y,BLUE);

	Vec2 p = TransformedView_WorldScreenPos(&tv,rect.p);
	Vec2 d = TransformedView_WorldScreenLength(&tv,rect.d);
	RenderRect(p.x,p.y,d.x,d.y,RED);

	InteractionSystem_Render(WINDOW_STD_ARGS,&menu,500.0f,64.0f);
}
void Delete(AlxWindow* w){
    InteractionSystem_Free(&menu);
}

int main(){
    if(Create("Interaction System",2200,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}