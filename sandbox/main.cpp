#include <raylibZero.h>

static Actor poly;
PhysicsBodyLite body;

int xs = 300;
int ys = -300;

void Draw(void)
{
	fill(NewColor(0, 255, 251));
	
	rect(WIDTH/2, HEIGHT/2, 50, 50, 45, BLUE);

	circle(WIDTH-60/2, HEIGHT/2, 25, RED, false);

	line(20, HEIGHT/2, HEIGHT-100, 100, WHITE);

	DrawActor(poly);
}

void Update()
{
	poly.Move(xs, ys);

	if (poly.GetPos().x > WIDTH-poly.GetWidth()/2)
	{
		poly.SetX(WIDTH-poly.texture.width/2);
		xs *= -1;
	}
	else if (poly.GetPos().x < poly.texture.width/2)
	{
		poly.SetX(poly.texture.width/2);
		xs *= -1;
	}

	if (poly.GetPos().y > HEIGHT-poly.texture.height/2)
	{
		poly.SetY(HEIGHT-poly.texture.height/2);
		ys *= -1;
	}
	else if (poly.GetPos().y < poly.texture.height/2)
	{
		poly.SetY(poly.texture.height/2);
		ys *= -1;
	}
}



void Input(void)
{
	if (IsKeyPressed(KEY_E))
		CreateBodyRect(0, HEIGHT/2, 50, 50, RED, true);

}

int main(void)
{
	Init(400, 400, "Hello, world!");

	poly = InitActor("image.png", 50, 50, 0);
	poly.SetSize(50, 50);

	PhysicsBodyLite boxA = InitBodyRect(0, HEIGHT/2, 50, 50, RED, true);
	PhysicsBodyLite boxB = InitBodyRect(WIDTH/2, HEIGHT/2+100, 50, 50, GREEN, true);
	PhysicsBodyLite boxC = InitBodyRect(WIDTH/2, HEIGHT/2, 50, 50, BLUE, true);

	PhysicsBodyLite floor = InitBodyRect(0, HEIGHT, WIDTH*2, 50, GREEN, true);
	floor.body->enabled = false;

	BeginGame();

	return 0;
}