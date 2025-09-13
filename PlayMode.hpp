#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode
{
	PlayMode();
	virtual ~PlayMode();

	// functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	// input tracking:
	struct Button
	{
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up, jump;

	// local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	Scene::Transform *player = nullptr;
	std::vector<Scene::Transform *> platforms;

	// Acceleration and max speed of the fish, accounting for the smaller parent node of the mesh
	const float playerAcceleration = 5.0f;

	// Player and shark speeds have different units because of their scale in blender
	float playerMaxSpeed = 10.0f;

	// Player and shark speeds have different units because of their scale in blender
	float jumpSpeed = 10.0f;

	// Gravitational force
	float gravity = 9.81f;

	glm::vec3 playerSpeed = glm::vec3(0.0f);

	// Position of the player in the previous frame
	glm::vec3 previous_player_pos;
	// Platform on which the player is
	Scene::Transform *player_platform = nullptr;

	// Checks if the player is colliding with the top of a given platform and applies collision
	bool collide_platform_top(Scene::Transform *platform);

	// Checks if the player is colliding with the side of a given platform and applies collision
	bool collide_platform_side(Scene::Transform *platform);

	// music coming from the tip of the leg (as a demonstration):
	std::shared_ptr<Sound::PlayingSample> leg_tip_loop;

	// car honk sound:
	std::shared_ptr<Sound::PlayingSample> honk_oneshot;

	// camera:
	Scene::Camera *camera = nullptr;
};
