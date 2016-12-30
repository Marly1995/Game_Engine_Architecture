#include "includes.h";

using namespace std;

// tag::globalVariables[]
std::string exeName;
SDL_Window *win; //pointer to the SDL_Window
SDL_GLContext context; //the SDL_GLContext
int frameCount = 0;
std::string frameLine = "";

int renderMode = 1;
vector<glm::vec3> positionVectorData;
vector<GLfloat> positionVertexData;
vector<GLfloat> powerVertexData;
vector<GLfloat> histogramVertexData;
vector<GLfloat> heatmapVertexData;
int positionIterator = 0;
char* fileDirectory = ("C:/Users/Marlon/Documents/PositionLogFile.txt");
// end::globalVariables[]

// tag::loadShader[]
std::string loadShader(const string filePath) {
	std::ifstream fileStream(filePath, std::ios::in | std::ios::binary);
	if (fileStream)
	{
		string fileData((std::istreambuf_iterator<char>(fileStream)),
			(std::istreambuf_iterator<char>()));

		cout << "Shader Loaded from " << filePath << endl;
		return fileData;
	}
	else
	{
		cerr << "Shader could not be loaded - cannot read file " << filePath << ". File does not exist." << endl;
		return "";
	}
}
// end::loadShader[]

//our variables
bool done = false;

// tag::vertexData[]
//the data about our geometry
const GLfloat vertexData[] = {
	//	 X        Y            Z          R     G     B      A
	0.000f,  0.500f,  0.000f,    
	-0.433f, -0.250f,  0.000f,   
	0.433f, -0.250f,  0.000f
};
// end::vertexData[]

// tag::gameState[]
//the translation vector we'll pass to our GLSL program
glm::vec3 position1 = { 0.0f, 0.0f, 0.0f };
// end::gameState[]

// tag::GLVariables[]
//our GL and GLSL variables
//programIDs
GLuint theProgram; //GLuint that we'll fill in to refer to the GLSL program (only have 1 at this point)

				   //attribute locations
GLint positionLocation; //GLuint that we'll fill in with the location of the `position` attribute in the GLSL
GLint vertexColorLocation; //GLuint that we'll fill in with the location of the `vertexColor` attribute in the GLSL

						   //uniform location
GLint modelMatrixLocation;
GLint viewMatrixLocation;
GLint projectionMatrixLocation;

GLuint vertexDataBufferObject;
GLuint vertexArrayObject;
// end::GLVariables[]



// end Global Variables
/////////////////////////

// tag::initialise[]
void initialise()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	cout << "SDL initialised OK!\n";
}
// end::initialise[]

// tag::createWindow[]
void createWindow()
{
	//get executable name, and use as window title
	int beginIdxWindows = exeName.rfind("\\"); //find last occurrence of a backslash
	int beginIdxLinux = exeName.rfind("/"); //find last occurrence of a forward slash
	int beginIdx = max(beginIdxWindows, beginIdxLinux);
	std::string exeNameEnd = exeName.substr(beginIdx + 1);
	const char *exeNameCStr = exeNameEnd.c_str();

	//create window
	win = SDL_CreateWindow(exeNameCStr, 100, 100, 600, 600, SDL_WINDOW_OPENGL); //same height and width makes the window square ...

																				//error handling
	if (win == nullptr)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	cout << "SDL CreatedWindow OK!\n";
}
// end::createWindow[]

// tag::setGLAttributes[]
void setGLAttributes()
{
	int major = 3;
	int minor = 3;
	cout << "Built for OpenGL Version " << major << "." << minor << endl; //ahttps://en.wikipedia.org/wiki/OpenGL_Shading_Language#Versions
																		  // set the opengl context version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //core profile
	cout << "Set OpenGL context to versicreate remote branchon " << major << "." << minor << " OK!\n";
}
// tag::setGLAttributes[]

// tag::createContext[]
void createContext()
{
	setGLAttributes();

	context = SDL_GL_CreateContext(win);
	if (context == nullptr) {
		SDL_DestroyWindow(win);
		std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	cout << "Created OpenGL context OK!\n";
}
// end::createContext[]

// tag::initGlew[]
void initGlew()
{
	GLenum rev;
	glewExperimental = GL_TRUE; //GLEW isn't perfect - see https://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
	rev = glewInit();
	if (GLEW_OK != rev) {
		std::cerr << "GLEW Error: " << glewGetErrorString(rev) << std::endl;
		SDL_Quit();
		exit(1);
	}
	else {
		cout << "GLEW Init OK!\n";
	}
}
// end::initGlew[]

// tag::createShader[]
GLuint createShader(GLenum eShaderType, const std::string &strShaderFile)
{
	GLuint shader = glCreateShader(eShaderType);
	//error check
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}
// end::createShader[]

// tag::createProgram[]
GLuint createProgram(const std::vector<GLuint> &shaderList)
{
	GLuint program = glCreateProgram();

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(program, shaderList[iLoop]);

	return program;
}
// end::createProgram[]
void buildHeatmap()
{
	int xSpread[100] = { 0 };
	int ySpread[100] = { 0 };
	int spread[100][100] = { 0 };

	int range = positionVertexData.size() / 7;
	float increment = ((1 / range) * 10);

	float xMin = 0, yMin = 0, xMax = 0, yMax = 0;

	for (int i = 0; i < range; i++)
	{
		float xTemp = positionVectorData[i].x;
		float yTemp = positionVectorData[i].y;

		if (xTemp > xMax) { xMax = xTemp; }
		if (xTemp < xMin) { xMin = xTemp; }
		if (yTemp > yMax) { yMax = yTemp; }
		if (yTemp < yMin) { yMin = yTemp; }
	}

	float xRange = xMax - xMin;
	float yRange = yMax - yMin;

	float xIncrement = xRange / 100;
	float yIncrement = yRange / 100;

	for (int i = 0; i < range; i++)
	{
		float xTemp = positionVectorData[i].x;
		float yTemp = positionVectorData[i].y;

		for (int z = 1; z < 101; z++)
		{
			if (xTemp >= xIncrement * z && xTemp < xIncrement * (z+1))
			{
				for (int p = 1; p < 101; p++)
				{
					if (yTemp >= yIncrement * p && yTemp < yIncrement * (p + 1))
					{
						spread[z - 1][p - 1]++;
					}
				}
			}
			
		}
	}

	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			heatmapVertexData.push_back(-1.0f + (x*0.02f));
			heatmapVertexData.push_back(-1.0f + (y*0.02f));
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(1.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(spread[x][y]);
			// point 2
			heatmapVertexData.push_back(-1.0f + (x*0.02f));
			heatmapVertexData.push_back(-0.98f + (y*0.02f));
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(1.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(spread[x][y]);
			//point 3
			heatmapVertexData.push_back(-0.98f + (x*0.02f));
			heatmapVertexData.push_back(-1.0f + (y*0.02f));
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(1.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(spread[x][y]);

			//point 1
			heatmapVertexData.push_back(-1.0f + (x*0.02f));
			heatmapVertexData.push_back(-0.98f + (y*0.02f));
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(1.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(spread[x][y]);
			//point 2
			heatmapVertexData.push_back(-0.98f + (x*0.02f));
			heatmapVertexData.push_back(-0.98f + (y*0.02f));
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(1.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(spread[x][y]);
			//point 3
			heatmapVertexData.push_back(-0.98f + (x*0.02f));
			heatmapVertexData.push_back(-1.0f + (y*0.02f));
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(1.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(0.0f);
			heatmapVertexData.push_back(spread[x][y]);
		}
	}
}
void buildHistogram()
{
	int spread[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	float temp;
	int range = powerVertexData.size();
	float increment = 2.0f/range;
	for (int i = 0; i < range; i++)
	{
		temp = powerVertexData[i];
		
		if (temp <= 300) { spread[0]++; }
		else if (temp > 300 && temp <= 600) { spread[1]++; }
		else if (temp > 600 && temp <= 900) { spread[2]++; }
		else if (temp > 900 && temp <= 1200) { spread[3]++; }
		else if (temp > 1200 && temp <= 1500) { spread[4]++; }
		else if (temp > 1500 && temp <= 1800) { spread[5]++; }
		else if (temp > 1800 && temp <= 2100) { spread[6]++; }
		else if (temp > 2100 && temp <= 2400) { spread[7]++; }
		else if (temp > 2400 && temp <= 2700) { spread[8]++; }
		else if (temp > 2700 && temp <= 3000) { spread[9]++; }
	}
	float xpos = -1.0f;
	for (int i = 0; i < 10; i++)
	{
		// point 1
		histogramVertexData.push_back(xpos);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		// point 2
		histogramVertexData.push_back(xpos);
		histogramVertexData.push_back(spread[i] * increment);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		//point 3
		histogramVertexData.push_back(xpos + 0.05f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);

		//point 1
		histogramVertexData.push_back(xpos);
		histogramVertexData.push_back(spread[i] * increment);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		//point 2
		histogramVertexData.push_back(xpos + 0.05f);
		histogramVertexData.push_back(spread[i] * increment);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		//point 3
		histogramVertexData.push_back(xpos + 0.05f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(0.0f);
		histogramVertexData.push_back(1.0f);

		cout << spread[i] << endl;
		xpos += 0.1f;
	}
}

// tag::loadFile[]
void loadPowerFile()
{
	ifstream file;
	string line;
	string number;
	float x;
	powerVertexData.clear();
	if (fileDirectory != nullptr)
	{
		file.open(fileDirectory);
	}
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		int dataPosition = 0;
		while (getline(file, line))
		{
			if (line == "power ")
			{
			}
			else
			{
				number = line;
				x = stof(number);
				powerVertexData.push_back(x);
			}
		}
		SDL_Log("Should have finished writing!\n");
		file.close();
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
	}
}

void loadPositionFile()
{
	ifstream file;
	string line;
	string number;
	positionVertexData.clear();
	if (fileDirectory != nullptr)
	{
		file.open(fileDirectory);
	}
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		int dataPosition = 0;
		while (getline(file, line))
		{
			int i;
			int k = 0;
			float x, y, z;
			x = 0;
			y = 0;
			z = 0;
			if (line == "position ")
			{
			}
			else
			{
				for (i = 4; i < line.size(); i++)
				{
					if (line[i] != ',' && line[i] != ')')
					{
						number += line[i];
					}
					else if (line[i] == ',' && k == 0)
					{
						x = stof(number);
						k++;
						i += 3;
						number = "";
					}
					else if (line[i] == ',' || line[i] == ')' && k == 1)
					{
						y = stof(number);
						k++;
						i += 3;
						number = "";
					}
					else if (line[i] == ')' && k == 2)
					{
						z = stof(number);
						number = "";
					}
				}
				positionVectorData.push_back(glm::vec3(x / 3000.0f, y / 3000.0f, z / 3000.0f));

				positionVertexData.push_back(x / 3000.0f);
				positionVertexData.push_back(y / 3000.0f);
				positionVertexData.push_back(z / 3000.0f);
				positionVertexData.push_back(1.0f);
				positionVertexData.push_back(0.0f);
				positionVertexData.push_back(0.0f);
				positionVertexData.push_back(1.0f);
			}
		}
		SDL_Log("Should have finished writing!\n");
		file.close();
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
	}
	buildHeatmap();
}

int loadFile()
{
	ifstream file;
	string line;
	if (fileDirectory != nullptr)
	{
		file.open(fileDirectory);
	}
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		getline(file, line);
		if (line == "position ")
		{
			loadPositionFile();
			file.close();
			return 1;
		}
		else if (line == "power ")
		{
			loadPowerFile();
			file.close();
			return 2;
		}
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
		return 0;
	}
}

// end::loadFile[]

// tag::initializeProgram[]
void initializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(createShader(GL_VERTEX_SHADER, loadShader("C:/Users/Marlon/Documents/GitHub/Game_Engine_Architecture/vertexShader.glsl")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, loadShader("C:/Users/Marlon/Documents/GitHub/Game_Engine_Architecture/fragmentShader.glsl")));

	theProgram = createProgram(shaderList);
	if (theProgram == 0)
	{
		cerr << "GLSL program creation error." << std::endl;
		SDL_Quit();
		exit(1);
	}
	else {
		cout << "GLSL program creation OK! GLUint is: " << theProgram << std::endl;
	}

	// tag::glGetAttribLocation[]
	positionLocation = glGetAttribLocation(theProgram, "position");
	vertexColorLocation = glGetAttribLocation(theProgram, "vertexColor");
	// end::glGetAttribLocation[]

	// tag::glGetUniformLocation[]
	modelMatrixLocation = glGetUniformLocation(theProgram, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(theProgram, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(theProgram, "projectionMatrix");

	//only generates runtime code in debug mode
	SDL_assert_release(modelMatrixLocation != -1);
	SDL_assert_release(viewMatrixLocation != -1);
	SDL_assert_release(projectionMatrixLocation != -1);
	// end::glGetUniformLocation[]

	//clean up shaders (we don't need them anymore as they are no in theProgram
	for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}
// end::initializeProgram[]

// tag::initializeVertexArrayObject[]
void initializeVertexArrayObject()
{
	// setup a GL object (a VertexArrayObject) that stores how to access data and from where
	glGenVertexArrays(1, &vertexArrayObject); //create a Vertex Array Object
	cout << "Vertex Array Object created OK! GLUint is: " << vertexArrayObject << std::endl;

	glBindVertexArray(vertexArrayObject); //make the just created vertexArrayObject the active one

	glBindBuffer(GL_ARRAY_BUFFER, vertexDataBufferObject); //bind vertexDataBufferObject

	glEnableVertexAttribArray(positionLocation); //enable attribute at index positionLocation
	glEnableVertexAttribArray(vertexColorLocation); //enable attribute at index vertexColorLocation

													// tag::glVertexAttribPointer[]
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, (7 * sizeof(GL_FLOAT)), (GLvoid *)(0 * sizeof(GLfloat))); //specify that position data contains four floats per vertex, and goes into attribute index positionLocation
	glVertexAttribPointer(vertexColorLocation, 4, GL_FLOAT, GL_FALSE, (7 * sizeof(GL_FLOAT)), (GLvoid *)(3 * sizeof(GLfloat))); //specify that position data contains four floats per vertex, and goes into attribute index vertexColorLocation
																																// end::glVertexAttribPointer[]

	glBindVertexArray(0); //unbind the vertexArrayObject so we can't change it

						  //cleanup
	glDisableVertexAttribArray(positionLocation); //disable vertex attribute at index positionLocation
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind array buffer

}
// end::initializeVertexArrayObject[]

// tag::initializeVertexBuffer[]

void remakeVertexBuffer(vector<GLfloat> data)
{
	glGenBuffers(1, &vertexDataBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexDataBufferObject);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data.front(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	cout << "vertexDataBufferObject created OK! GLUint is: " << vertexDataBufferObject << std::endl;

	initializeVertexArrayObject();
}

void initializeVertexBuffer()
{
	glGenBuffers(1, &vertexDataBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexDataBufferObject);
	glBufferData(GL_ARRAY_BUFFER, positionVertexData.size() * sizeof(GLfloat), &positionVertexData.front(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	cout << "vertexDataBufferObject created OK! GLUint is: " << vertexDataBufferObject << std::endl;

	initializeVertexArrayObject();
}
// end::initializeVertexBuffer[]

// tag::loadAssets[]
void loadAssets()
{
	initializeProgram(); //create GLSL Shaders, link into a GLSL program, and get IDs of attributes and variables

	initializeVertexBuffer(); //load data into a vertex buffer

	cout << "Loaded Assets OK!\n";
}
// end::loadAssets[]

// tag::handleInput[]
void handleInput()
{
	//Event-based input handling
	//The underlying OS is event-based, so **each** key-up or key-down (for example)
	//generates an event.
	//  - https://wiki.libsdl.org/SDL_PollEvent
	//In some scenarios we want to catch **ALL** the events, not just to present state
	//  - for instance, if taking keyboard input the user might key-down two keys during a frame
	//    - we want to catch based, and know the order
	//  - or the user might key-down and key-up the same within a frame, and we still want something to happen (e.g. jump)
	//  - the alternative is to Poll the current state with SDL_GetKeyboardState

	SDL_Event event; //somewhere to store an event

					 //NOTE: there may be multiple events per frame
	while (SDL_PollEvent(&event)) //loop until SDL_PollEvent returns 0 (meaning no more events)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			done = true; //set donecreate remote branch flag if SDL wants to quit (i.e. if the OS has triggered a close event,
						 //  - such as window close, or SIGINT
			break;

			//keydown handling - we should to the opposite on key-up for direction controls (generally)
		case SDL_KEYDOWN:
			//Keydown can fire repeatable if key-repeat is on.
			//  - the repeat flag is set on the keyboard event, if this is a repeat event
			//  - in our case, we're going to ignore repeat events
			//  - https://wiki.libsdl.org/SDL_KeyboardEvent
			if (!event.key.repeat)
				switch (event.key.keysym.sym)
				{
					//hit escape to exit
				case SDLK_ESCAPE: done = true;
					break;
				case SDLK_1: renderMode = 1;
					break;
				case SDLK_2: renderMode = 2;
				}
			break;

		case SDL_DROPFILE:
			fileDirectory = event.drop.file;
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_INFORMATION,
				"File Dropped on Window",
				fileDirectory,
				win
			);
			int type = loadFile();
			switch (type) 
			{
			case 1: remakeVertexBuffer(heatmapVertexData);
				break;
			case 2: buildHistogram();
				remakeVertexBuffer(histogramVertexData);
				break;
			}
		}
	}
}
// end::handleInput[]

// tag::updateSimulation[]
void updateSimulation(double simLength = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
	//WARNING - we should calculate an appropriate amount of time to simulate - not always use a constant amount of time
	// see, for example, http://headerphile.blogspot.co.uk/2014/07/part-9-no-more-delays.html
	/*if (positionIterator < positionData.size()) 
	{
		position1 = positionData[positionIterator];
		cout << "  " << positionData[positionIterator].x << "  " << positionData[positionIterator].y << "  " << positionData[positionIterator].z << "\n";
		positionIterator++;
	}*/
	//else { positionIterator = 0; }
}
// end::updateSimulation[]

// tag::preRender[]
void preRender()
{
	glViewport(0, 0, 600, 600); //set viewpoint
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set clear colour
	glClear(GL_COLOR_BUFFER_BIT); //clear the window (technical the scissor box bounds)
}
// end::preRender[]

// tag::render[]
void render()
{
	glUseProgram(theProgram); //installs the program object specified by program as part of current rendering state

	glBindVertexArray(vertexArrayObject);

	//set projectionMatrix - how we go from 3D to 2D
	glUniformMatrix4fv(projectionMatrixLocation, 1, false, glm::value_ptr(glm::mat4(1.0)));

	//set viewMatrix - how we control the view (viewpoint, view direction, etc)
	glUniformMatrix4fv(viewMatrixLocation, 1, false, glm::value_ptr(glm::mat4(1.0f)));

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position1);

	switch (renderMode)
	{

	case 1:
		glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));
		glLineWidth(5);
		glDrawArrays(GL_LINE_STRIP, 0, positionVertexData.size() / 7);
		break;

	case 2:
		glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));
		glDrawArrays(GL_TRIANGLES, 0, histogramVertexData.size() / 7);
		break;

	}
	glBindVertexArray(0);

	glUseProgram(0); //clean up
}
// end::render[]

// tag::postRender[]
void postRender()
{
	SDL_GL_SwapWindow(win);; //present the frame buffer to the display (swapBuffers)
	frameLine += "Frame: " + std::to_string(frameCount++);
	cout << "\r" << frameLine << std::flush;
	frameLine = "";
}
// end::postRender[]

// tag::cleanUp[]
void cleanUp()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	cout << "Cleaning up OK!\n";
}
// end::cleanUp[]

// tag::main[]
int main(int argc, char* args[])
{
	exeName = args[0];
	//setup
	//- do just once
	loadFile();

	initialise();

	createWindow();

	createContext();

	initGlew();

	glViewport(0, 0, 600, 600); //should check what the actual window res is?

	

								//do stuff that only needs to happen once
								//- create shaders
								//- load vertex data
	loadAssets();

	while (!done) //loop until done flag is set)
	{
		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(); // this should ONLY SET VARIABLES according to simulation

		preRender();

		render(); // this should render the world state according to VARIABLES -

		postRender();

	}

	//cleanup and exit
	cleanUp();
	SDL_Quit();

	return 0;
}
// end::main[]