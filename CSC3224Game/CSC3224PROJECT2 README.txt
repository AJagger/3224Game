The major new additions for the game are the:

GameRules Class
StandardGameObject Class
StandardKeyInterpreter Class

which are present within the Game/CSC3224Game folder along with all the assets for the game.

The assets are loaded using the ResourceLoader class which has had minor modifications from the initial engine submission.

While a fair few of the original engine files have been modified, one major modification is the CustContactListener class which was added for use with
Box2D to allow game rules to be executed on collision detection.

The game only has the one level in this submission and still suffers from the crash on exit that the original engine did.
