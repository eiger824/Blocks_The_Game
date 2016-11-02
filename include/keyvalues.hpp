static const int LEFT = 16777234;
static const int UP = LEFT + 1;
static const int RIGHT = UP + 1;
static const int DOWN = RIGHT + 1;
static const int ESC = 16777216;
static const int ENTER = 16777220;
static const int PAUSE = 16777224;
static const int CTRL = 16777249;
static const int INSERT = 16777222;
static const int SHIFT = 16777248;
static const int CAPS_LOCK= 16777252;
static const int NUM_LOCK = 16777253;
static const int SCROLL_LOCK = 16777254;
static const int WIN = 16777250;
static const int ALTGR = 16781571;
static const int ALT = 16777251;
static const int SIDE_ENTER = 0;

//globals
QString PREFIX = "images/";
QString YELLOW = PREFIX + "yellow_selected.png";
QString RED = PREFIX + "red_selected.png";
QString EASY = "easy";
QString HARD = "hard";

//blacklist with initial keys
QList<int> BLACKLIST = (QList<int>()
			<< INSERT
			<< CTRL
			<< ESC
			<< PAUSE
			<< CTRL
			<< INSERT
			<< SHIFT
			<< CAPS_LOCK
			<< NUM_LOCK
			<< SCROLL_LOCK
			<< WIN
			<< ALTGR
			<< ALT
			<< SIDE_ENTER
			);

//list with colors
QStringList COLORS = (QStringList()
		      << "black.png"
		      << "green.png"
		      << "orange.png"
		      << "red.png"
		      << "blue.png"
		      << "yellow.png"
		      << "rosa.png");
