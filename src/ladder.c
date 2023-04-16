#include <raylib.h>
#include <rcamera.h>

#include <stdio.h>

/* The Ladder's other code */
#include "sound.h"
#include "world/staircase.h"
#include "player/physics.h"

#include "player/player.h"

#define MAX_STAMINA  150
#define FRAMES_TO_WAIT 3

#define DEBUG

void _(){}

int main(void){
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	#ifndef DEBUG
		SetTraceLogCallback(_);
	#endif

	player_t player;

	InitAudioDevice();
	Sound run1 = LoadSound("src/res/Run1.ogg");
	Sound run2 = LoadSound("src/res/Run2.ogg");
	

	InitWindow(screenWidth, screenHeight, "The Ladder");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = { 0 };
	camera.position = (Vector3){ -10.6f, 2.0f, -1.3f };    // Camera position
	camera.target = (Vector3){ -0.2f, 1.9f, 2.6f };      // Camera looking at point
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

	int stamina = 150; // MAX_STAMINA
	float speed_modifier = 0.1f;

	int framect = 0;
	int notplaying = 0; // sound

	stair_t original_stair = {
		.color = GRAY,
		.dimensions = (Vector2){-10.0f, 0.0f},
		#ifdef DEBUG
			.y_pos = 0.0f,
		#else
			.y_pos = 2.0f,
		#endif
		.width = WIDTH_STAIR
	};


	DisableCursor();                    // Limit cursor to relative movement inside the window

	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose()) {
		// Update
		//----------------------------------------------------------------------------------

		if((IsKeyDown(KEY_W) || IsKeyDown(KEY_S)
		   || IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) &&
			 !(IsKeyDown(KEY_LEFT_SHIFT)))
			notplaying = _playsound(run2, framect, notplaying);
		
		if((IsKeyDown(KEY_W) || IsKeyDown(KEY_S)
		   || IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) &&
			 (IsKeyDown(KEY_LEFT_SHIFT)) && 
			 (stamina != 0 || stamina > 0)){
				notplaying = _playsound(run1, framect, notplaying);


			// stamina and stuff
			if(stamina != 0 || stamina > 0) {
				stamina--;
				speed_modifier = 0.2f;
			}
		} else {
			if(framect % 3 == 0)
				if(stamina != 150 || !(stamina >= 150)) stamina++;
			speed_modifier = 0.1f;
		}
		UpdateCameraPro(&camera,
			(Vector3){
				(IsKeyDown(KEY_W))*speed_modifier -      // Move forward-backward
				(IsKeyDown(KEY_S))*speed_modifier,    
				(IsKeyDown(KEY_D))*speed_modifier -   // Move right-left
				(IsKeyDown(KEY_A))*speed_modifier,
				move_down__(camera.position.y, player, original_stair,
										camera) // up down
			},
			(Vector3){
				GetMouseDelta().x*0.05f,                            // Rotation: yaw
				GetMouseDelta().y*0.05f,                            // Rotation: pitch
				0.0f                                               // Rotation: roll
			},
			GetMouseWheelMove()*2.0f);                              // Move to target (zoom)

		// After we update the camera, let's update the players
		// position
		player.position = (Vector3){
			camera.position.x,
			camera.position.y,
			camera.position.z
		};
			

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

			ClearBackground(BLACK);


			BeginMode3D(camera);

				_drawstaircase_z(original_stair, 50);
				DrawCube((Vector3){10.0f, 2.0f, 8.0f}, 10.0f, 10.0f,
								10.0f, RED);

			EndMode3D();
			
			// Debug info
			#ifdef DEBUG

				DrawRectangle(560, 5, 220, 50, Fade(SKYBLUE, 1.0f));
				DrawRectangleLines(560, 5, 220, 50, BLUE);

				DrawText(TextFormat("Coordinates (x,y,z) -> (%.1f, %.1f, %.1f)",
														camera.position.x, camera.position.y, camera.position.z),
														570, 15, 10, BLACK);
				DrawText(TextFormat("Looking at (x,y,z) -> (%.1f, %.1f, %.1f)",
														camera.target.x, camera.target.y, camera.target.z),
														570, 30, 10, BLACK);

			#endif

			// draw pointer
			DrawCircle(screenWidth/2, screenHeight/2,
								 4, WHITE);

			
			DrawSphere((Vector3){camera.position.x, camera.position.y,
									camera.position.z}, 10, RED);


			// stamina bar
			DrawRectangle(10, 10, stamina, 25, WHITE);
			DrawRectangleLines(10, 10, 150, 25, BLACK);
		EndDrawing();
		//----------------------------------------------------------------------------------
	
		framect++;
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}