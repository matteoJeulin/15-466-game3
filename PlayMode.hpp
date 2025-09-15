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
	Scene::Transform *goal = nullptr;
	std::vector<Scene::Transform *> platforms;

	// Acceleration and max speed of the player, accounting for the smaller parent node of the mesh
	const float playerAcceleration = 7.5f;

	const float playerMaxSpeed = 10.0f;

	// Player and shark speeds have different units because of their scale in blender
	float jumpSpeed = 10.0f;

	// Gravitational force
	float gravity = 19.62f;

	bool noclip = false;
	bool won = false;

	glm::vec3 playerSpeed = glm::vec3(0.0f);

	// Position of the player in the previous frame
	glm::vec3 previous_player_pos;
	// Platform on which the player is
	Scene::Transform *player_platform = nullptr;

	bool jumping = false;

	float timer = 0.0f;

	glm::vec3 background_colour = glm::vec3(0.0f, 0.0f, 0.0f);

	// Checks if the player is colliding with the top of a given platform and applies collision
	bool collide_platform_top(Scene::Transform *platform);

	// Checks if the player is colliding with the side of a given platform and applies collision
	bool collide_platform_side(Scene::Transform *platform);

	float bonk_frequency = 6.0f;
	float bonk_length = 1.5f;
	bool playing_bonk = false;

	// car honk sound:
	std::shared_ptr<Sound::PlayingSample> bonk_oneshot;

	// camera:
	Scene::Camera *camera = nullptr;
};
