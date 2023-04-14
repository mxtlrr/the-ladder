#include <raylib.h>
#include <rcamera.h>

#include <stdio.h>

#define MAX_STAMINA  150
#define FRAMES_TO_WAIT 3

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void){
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "The Ladder");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = { 0 };
	camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
	camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

	int stamina = 150; // MAX_STAMINA
	float speed_modifier = 0.1f;

	int framect = 0;


	DisableCursor();                    // Limit cursor to relative movement inside the window

	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------

		// Camera PRO usage example (EXPERIMENTAL)
		// This new camera function allows custom movement/rotation values to be directly provided
		// as input parameters, with this approach, rcamera module is internally independent of raylib inputs
		if(IsKeyDown(KEY_LEFT_SHIFT)){
			if(stamina != 0 || stamina > 0) stamina--;
			speed_modifier = 0.2f;
		} else {
			if(framect % 3 == 0)
				if(stamina != 150 || !(stamina >= 150)) stamina++;
			speed_modifier = 0.1f;
		}
		UpdateCameraPro(&camera,
			(Vector3){
				(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*speed_modifier -      // Move forward-backward
				(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*speed_modifier,    
				(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*speed_modifier -   // Move right-left
				(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*speed_modifier,
				0.0f // up down
			},
			(Vector3){
				GetMouseDelta().x*0.05f,                            // Rotation: yaw
				GetMouseDelta().y*0.05f,                            // Rotation: pitch
				0.0f                                               // Rotation: roll
			},
			GetMouseWheelMove()*2.0f);                              // Move to target (zoom)

			

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

			ClearBackground(BLACK);


			BeginMode3D(camera);

					DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
					
					DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
					DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
					DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
					DrawCube((Vector3){ 0.0f, 2.5f, -16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

			EndMode3D();

			DrawRectangle(560, 5, 220, 50, Fade(SKYBLUE, 1.0f));
			DrawRectangleLines(560, 5, 220, 50, BLUE);

			DrawText(TextFormat("Coordinates (x,y,z) -> (%.1f, %.1f, %.1f)",
													camera.position.x, camera.position.y, camera.position.z),
													570, 15, 10, BLACK);
			DrawText(TextFormat("Looking at (x,y,z) -> (%.1f, %.1f, %.1f)",
												  camera.target.x, camera.target.y, camera.target.z),
													570, 30, 10, BLACK);


			// draw pointer
			DrawCircle(screenWidth/2, screenHeight/2,
								 4, WHITE);


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