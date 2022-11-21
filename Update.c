#include "Time.h"
#include "Keyboard.h"

#include "Game.h"

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif
void Update() {
	UpdateTime();
	UpdateKeyboard();

#ifdef DEBUG
	if (GetKey(VK_CONTROL) && GetKey(VK_MENU) && GetKeyDown('V')) {
		Entity* randomEntity = (Entity*)malloc(sizeof(Entity));
		if (randomEntity == NULL) exit(-1);
		randomEntity->pos.x = rand();
		randomEntity->pos.y = rand();
		randomEntity->type = _Player;
		VectorInsert(debugVector, randomEntity);
		//for (int i = 0; i < debugVector->length; i++) {
		//	DebugPrint("%d (%d, %d) Entity", i, debugVector->entities[i]->pos.x, debugVector->entities[i]->pos.y);
		//}
	}


	// Start of QuadTree Debug
	Rect debugQuadTreeRect = { .x = 0, .y = 0, .width = RAND_MAX + 1, .height = RAND_MAX + 1 };
	debugTree = CreateQuadTree(debugQuadTreeRect);
	for (int i = 0; i < debugVector->length; i++) {
		bool inserted = QuadTreeInsert(debugTree, debugVector->entities[i]);
	}

	if (GetKey(VK_CONTROL) && GetKey(VK_MENU) && GetKeyDown('Q')) DebugQuadTree(debugTree);
	if (GetKey(VK_CONTROL) && GetKey(VK_MENU) && GetKeyDown('R')) {
		Rect queryRect = { .x = 0, .y = 0, .width = 20000, .height = 20000 };
		Vector* queryResult = QuadTreeQuery(debugTree, queryRect);
		DebugPrint("QueryResult length is.. %d", queryResult->length);
		for (int i = 0; i < queryResult->length; i++) {
			DebugPrint("Query Entity: (%d, %d)", queryResult->entities[i]->pos.x, queryResult->entities[i]->pos.y);
		}
		DeleteVector(queryResult);
	}
	
	DeleteQuadTree(debugTree);
	// End of QuadTree Debug

	
#endif
}
