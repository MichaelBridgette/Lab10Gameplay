#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} Vertex;

Vertex vertex[36];
GLubyte triangles[36];

/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
		vsid,		//Vertex Shader ID
		fsid,		//Fragment Shader ID
		progID,		//Program ID
		vao = 0,	//Vertex Array ID
		vbo[1],		// Vertex Buffer ID
		positionID, //Position ID
		colorID,	// Color ID
		to,			// Texture ID 1 to 32
		textureID,	//Texture ID
		texelID;	// Texel ID

//const string filename = "texture.tga";
//const string filename = "cube.tga";

const string filename = "cube.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));


	/*
	MyVector3 v1 = MyVector3(-0.5f,-0.5f,0.0f);
	MyVector3 v2 = MyVector3(-0.5f,0.5f,0.0f);
	MyVector3 v3 = MyVector3(0.5f,0.5f,0.0f);
	MyVector3 v4 = MyVector3(0.5f,-0.5f,0.0f);
	MyVector3 v5 = MyVector3(-0.5f,-0.5f,0.2f);
	MyVector3 v6 = MyVector3(-0.5f,0.5f,0.2f);
	MyVector3 v7 = MyVector3(0.5f,0.5f,0.2F);
	MyVector3 v8 = MyVector3(0.5f,-0.5f,0.2f);
	*/

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = v1.GetXf();
	vertex[0].coordinate[1] = v1.GetYf();
	vertex[0].coordinate[2] = v1.GetZf();

	vertex[1].coordinate[0] = v2.GetXf();
	vertex[1].coordinate[1] = v2.GetYf();
	vertex[1].coordinate[2] = v2.GetZf();

	vertex[2].coordinate[0] = v3.GetXf();
	vertex[2].coordinate[1] = v3.GetYf();
	vertex[2].coordinate[2] = v3.GetZf();

	vertex[3].coordinate[0] = v4.GetXf();
	vertex[3].coordinate[1] = v4.GetYf();
	vertex[3].coordinate[2] = v4.GetZf();

	vertex[4].coordinate[0] = v5.GetXf();
	vertex[4].coordinate[1] = v5.GetYf();
	vertex[4].coordinate[2] = v5.GetZf();

	vertex[5].coordinate[0] = v6.GetXf();
	vertex[5].coordinate[1] = v6.GetYf();
	vertex[5].coordinate[2] = v6.GetZf();

	vertex[6].coordinate[0] = v7.GetXf();
	vertex[6].coordinate[1] = v7.GetYf();
	vertex[6].coordinate[2] = v7.GetZf();

	vertex[7].coordinate[0] = v8.GetXf();
	vertex[7].coordinate[1] = v8.GetYf();
	vertex[7].coordinate[2] = v8.GetZf();

	vertex[0].color[0] = 1.0f;
	vertex[0].color[1] = 0.0f;
	vertex[0].color[2] = 0.0f;
	vertex[0].color[3] = 0.0f;

	vertex[1].color[0] = 0.0f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;
	vertex[1].color[3] = 0.0f;

	vertex[2].color[0] = 0.0f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 1.0f;
	vertex[2].color[3] = 0.0f;

	vertex[3].color[0] = 0.0f;
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 0.0f;
	vertex[3].color[3] = 1.0f;

	vertex[4].color[0] = 1.0f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;
	vertex[4].color[3] = 0.0f;

	vertex[5].color[0] = 1.0f;
	vertex[5].color[1] = 0.0f;
	vertex[5].color[2] = 1.0f;
	vertex[5].color[3] = 0.0f;

	vertex[6].color[0] = 1.0f;
	vertex[6].color[1] = 0.0f;
	vertex[6].color[2] = 0.0f;
	vertex[6].color[3] = 1.0f;

	vertex[7].color[0] = 1.0f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 1.0f;
	vertex[7].color[3] = 0.0f;

	vertex[0].texel[0] = 0.5f;
	vertex[0].texel[1] = 0.5f;

	vertex[1].texel[0] = 1.0f;
	vertex[1].texel[1] = 1.0f;

	vertex[2].texel[0] = 1.0f;
	vertex[2].texel[1] = 0.0f;

	/*Index of Poly / Triangle to Draw */
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;

	triangles[3] = 0;   triangles[4] = 2;   triangles[5] = 3;

	triangles[6] = 3;   triangles[7] = 2;   triangles[8] = 6;

	triangles[9] = 3;   triangles[10] = 6;   triangles[11] = 7;

	triangles[12] = 7;   triangles[13] = 6;   triangles[14] = 5;

	triangles[15] = 7;   triangles[16] = 5;   triangles[17] = 4;

	triangles[18] = 4;   triangles[19] = 5;   triangles[20] = 1;

	triangles[21] = 4;   triangles[22] = 1;   triangles[23] = 0;

	triangles[24] = 1;   triangles[25] = 5;   triangles[26] = 6;

	triangles[27] = 1;   triangles[28] = 6;   triangles[29] = 2;

	triangles[30] = 4;   triangles[31] = 0;   triangles[32] = 3;

	triangles[33] = 4;   triangles[34] = 3;   triangles[35] = 7;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"in vec2 sv_texel;"
		"out vec4 color;"
		"out vec2 texel;"
		"void main() {"
		"	color = sv_color;"
		"	texel = sv_texel;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"uniform sampler2D f_texture;"
		"in vec4 color;"
		"in vec2 texel;"
		"out vec4 fColor;"
		"void main() {"
		//"	fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
		"	fColor = texture(f_texture, texel.st);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	v1 = m1*v1;
	v2 = m1*v2;
	v3 = m1*v3;
	v4 = m1*v4;
	v5 = m1*v5;
	v6 = m1*v6;
	v7 = m1*v7;
	v8 = m1*v8;

	v1 = MyVector3(v1.GetXf(), v1.GetYf(), v1.GetZf() + 0.5f);
	v2 = MyVector3(v2.GetXf(), v2.GetYf(), v2.GetZf() + 0.5f);
	v3 = MyVector3(v3.GetXf(), v3.GetYf(), v3.GetZf() + 0.5f);
	v4 = MyVector3(v4.GetXf(), v4.GetYf(), v4.GetZf() + 0.5f);
	v5 = MyVector3(v5.GetXf(), v5.GetYf(), v5.GetZf() + 0.5f);
	v6 = MyVector3(v6.GetXf(), v6.GetYf(), v6.GetZf() + 0.5f);
	v7 = MyVector3(v7.GetXf(), v7.GetYf(), v7.GetZf() + 0.5f);
	v8 = MyVector3(v8.GetXf(), v8.GetYf(), v8.GetZf() + 0.5f);


	vertex[0].coordinate[0] = v1.GetXf();
	vertex[0].coordinate[1] = v1.GetYf();
	vertex[0].coordinate[2] = v1.GetZf();

	vertex[1].coordinate[0] = v2.GetXf();
	vertex[1].coordinate[1] = v2.GetYf();
	vertex[1].coordinate[2] = v2.GetZf();

	vertex[2].coordinate[0] = v3.GetXf();
	vertex[2].coordinate[1] = v3.GetYf();
	vertex[2].coordinate[2] = v3.GetZf();

	vertex[3].coordinate[0] = v4.GetXf();
	vertex[3].coordinate[1] = v4.GetYf();
	vertex[3].coordinate[2] = v4.GetZf();

	vertex[4].coordinate[0] = v5.GetX();
	vertex[4].coordinate[1] = v5.GetY();
	vertex[4].coordinate[2] = v5.GetZ();

	vertex[5].coordinate[0] = v6.GetX();
	vertex[5].coordinate[1] = v6.GetY();
	vertex[5].coordinate[2] = v6.GetZ();

	vertex[6].coordinate[0] = v7.GetX();
	vertex[6].coordinate[1] = v7.GetY();
	vertex[6].coordinate[2] = v7.GetZ();

	vertex[7].coordinate[0] = v8.GetX();
	vertex[7].coordinate[1] = v8.GetY();
	vertex[7].coordinate[2] = v8.GetZ();



	v1 = MyVector3(v1.GetXf(), v1.GetYf(), v1.GetZf() - 0.5f);
	v2 = MyVector3(v2.GetXf(), v2.GetYf(), v2.GetZf() - 0.5f);
	v3 = MyVector3(v3.GetXf(), v3.GetYf(), v3.GetZf() - 0.5f);
	v4 = MyVector3(v4.GetXf(), v4.GetYf(), v4.GetZf() - 0.5f);
	v5 = MyVector3(v5.GetXf(), v5.GetYf(), v5.GetZf() - 0.5f);
	v6 = MyVector3(v6.GetXf(), v6.GetYf(), v6.GetZf() - 0.5f);
	v7 = MyVector3(v7.GetXf(), v7.GetYf(), v7.GetZf() - 0.5f);
	v8 = MyVector3(v8.GetXf(), v8.GetYf(), v8.GetZf() - 0.5f);

	v1 = m2*v1;
	v2 = m2*v2;
	v3 = m2*v3;
	v4 = m2*v4;
	v5 = m2*v5;
	v6 = m2*v6;
	v7 = m2*v7;
	v8 = m2*v8;

	v1 = MyVector3(v1.GetXf(), v1.GetYf(), v1.GetZf() + 0.5f);
	v2 = MyVector3(v2.GetXf(), v2.GetYf(), v2.GetZf() + 0.5f);
	v3 = MyVector3(v3.GetXf(), v3.GetYf(), v3.GetZf() + 0.5f);
	v4 = MyVector3(v4.GetXf(), v4.GetYf(), v4.GetZf() + 0.5f);
	v5 = MyVector3(v5.GetXf(), v5.GetYf(), v5.GetZf() + 0.5f);
	v6 = MyVector3(v6.GetXf(), v6.GetYf(), v6.GetZf() + 0.5f);
	v7 = MyVector3(v7.GetXf(), v7.GetYf(), v7.GetZf() + 0.5f);
	v8 = MyVector3(v8.GetXf(), v8.GetYf(), v8.GetZf() + 0.5f);


	vertex[0].coordinate[0] = v1.GetXf();
	vertex[0].coordinate[1] = v1.GetYf();
	vertex[0].coordinate[2] = v1.GetZf();

	vertex[1].coordinate[0] = v2.GetXf();
	vertex[1].coordinate[1] = v2.GetYf();
	vertex[1].coordinate[2] = v2.GetZf();

	vertex[2].coordinate[0] = v3.GetXf();
	vertex[2].coordinate[1] = v3.GetYf();
	vertex[2].coordinate[2] = v3.GetZf();

	vertex[3].coordinate[0] = v4.GetXf();
	vertex[3].coordinate[1] = v4.GetYf();
	vertex[3].coordinate[2] = v4.GetZf();

	vertex[4].coordinate[0] = v5.GetX();
	vertex[4].coordinate[1] = v5.GetY();
	vertex[4].coordinate[2] = v5.GetZ();

	vertex[5].coordinate[0] = v6.GetX();
	vertex[5].coordinate[1] = v6.GetY();
	vertex[5].coordinate[2] = v6.GetZ();

	vertex[6].coordinate[0] = v7.GetX();
	vertex[6].coordinate[1] = v7.GetY();
	vertex[6].coordinate[2] = v7.GetZ();

	vertex[7].coordinate[0] = v8.GetX();
	vertex[7].coordinate[1] = v8.GetY();
	vertex[7].coordinate[2] = v8.GetZ();



	v1 = MyVector3(v1.GetXf(), v1.GetYf(), v1.GetZf() - 0.5f);
	v2 = MyVector3(v2.GetXf(), v2.GetYf(), v2.GetZf() - 0.5f);
	v3 = MyVector3(v3.GetXf(), v3.GetYf(), v3.GetZf() - 0.5f);
	v4 = MyVector3(v4.GetXf(), v4.GetYf(), v4.GetZf() - 0.5f);
	v5 = MyVector3(v5.GetXf(), v5.GetYf(), v5.GetZf() - 0.5f);
	v6 = MyVector3(v6.GetXf(), v6.GetYf(), v6.GetZf() - 0.5f);
	v7 = MyVector3(v7.GetXf(), v7.GetYf(), v7.GetZf() - 0.5f);
	v8 = MyVector3(v8.GetXf(), v8.GetYf(), v8.GetZf() - 0.5f);



	/*v1 = m3*v1;
	v2 = m3*v2;
	v3 = m3*v3;
	v4 = m3*v4;
	v5 = m3*v5;
	v6 = m3*v6;
	v7 = m3*v7;
	v8 = m3*v8;

	v1 = MyVector3(v1.GetXf(), v1.GetYf(), v1.GetZf() + 0.5f);
	v2 = MyVector3(v2.GetXf(), v2.GetYf(), v2.GetZf() + 0.5f);
	v3 = MyVector3(v3.GetXf(), v3.GetYf(), v3.GetZf() + 0.5f);
	v4 = MyVector3(v4.GetXf(), v4.GetYf(), v4.GetZf() + 0.5f);
	v5 = MyVector3(v5.GetXf(), v5.GetYf(), v5.GetZf() + 0.5f);
	v6 = MyVector3(v6.GetXf(), v6.GetYf(), v6.GetZf() + 0.5f);
	v7 = MyVector3(v7.GetXf(), v7.GetYf(), v7.GetZf() + 0.5f);
	v8 = MyVector3(v8.GetXf(), v8.GetYf(), v8.GetZf() + 0.5f);


	vertex[0].coordinate[0] = v1.GetXf();
	vertex[0].coordinate[1] = v1.GetYf();
	vertex[0].coordinate[2] = v1.GetZf();

	vertex[1].coordinate[0] = v2.GetXf();
	vertex[1].coordinate[1] = v2.GetYf();
	vertex[1].coordinate[2] = v2.GetZf();

	vertex[2].coordinate[0] = v3.GetXf();
	vertex[2].coordinate[1] = v3.GetYf();
	vertex[2].coordinate[2] = v3.GetZf();

	vertex[3].coordinate[0] = v4.GetXf();
	vertex[3].coordinate[1] = v4.GetYf();
	vertex[3].coordinate[2] = v4.GetZf();

	vertex[4].coordinate[0] = v5.GetX();
	vertex[4].coordinate[1] = v5.GetY();
	vertex[4].coordinate[2] = v5.GetZ();

	vertex[5].coordinate[0] = v6.GetX();
	vertex[5].coordinate[1] = v6.GetY();
	vertex[5].coordinate[2] = v6.GetZ();

	vertex[6].coordinate[0] = v7.GetX();
	vertex[6].coordinate[1] = v7.GetY();
	vertex[6].coordinate[2] = v7.GetZ();

	vertex[7].coordinate[0] = v8.GetX();
	vertex[7].coordinate[1] = v8.GetY();
	vertex[7].coordinate[2] = v8.GetZ();



	v1 = MyVector3(v1.GetXf(), v1.GetYf(), v1.GetZf() - 0.5f);
	v2 = MyVector3(v2.GetXf(), v2.GetYf(), v2.GetZf() - 0.5f);
	v3 = MyVector3(v3.GetXf(), v3.GetYf(), v3.GetZf() - 0.5f);
	v4 = MyVector3(v4.GetXf(), v4.GetYf(), v4.GetZf() - 0.5f);
	v5 = MyVector3(v5.GetXf(), v5.GetYf(), v5.GetZf() - 0.5f);
	v6 = MyVector3(v6.GetXf(), v6.GetYf(), v6.GetZf() - 0.5f);
	v7 = MyVector3(v7.GetXf(), v7.GetYf(), v7.GetZf() - 0.5f);
	v8 = MyVector3(v8.GetXf(), v8.GetYf(), v8.GetZf() - 0.5f);*/





	//Change vertex data
	

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}

