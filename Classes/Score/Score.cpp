#include "Score.h"
#include "Entity/EntityInfo.h"
#include "Character/Character.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

Score* Score::_instance;

Score* Score::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Score();
        _instance->init();
    }
    return _instance;
}

bool Score::init()
{
    scoreLabel = Label::createWithTTF("Score: 0", "fonts/Planes_ValMore.ttf", 64);
    this->addChild(scoreLabel);
    return true;
}

void Score::update(int value)
{
    score += value;
    scoreLabel->setString("Score: " + std::to_string(score));

}

void Score::reset()
{
    score = 0;
    scoreLabel->setString("Score: " + std::to_string(score));
}

void Score::saveToFile(std::string mapLevel, int score)
{
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "highscore.json";

	if (!FileUtils::getInstance()->isFileExist(path))
	{
		// create new 
		std::string content = FileUtils::getInstance()->getStringFromFile("default-highscore.json");
		FileUtils::getInstance()->writeStringToFile(content, path);
	}

	// read file
	auto highScoreContent = FileUtils::getInstance()->getStringFromFile(path);
	rapidjson::Document docs;
	docs.Parse(highScoreContent.c_str());

	// Check if the document is an object
	if (docs.IsObject()) {
		// Convert level to a const char*
		const char* thelevel = mapLevel.c_str();

		// Check if the level exists in the document
		if (docs.HasMember(thelevel)) {
			// Get the current high score for the level
			int highScore = docs[thelevel].GetInt();

			// If the new score is higher, update the high score
			if (highScore < score) {
				docs[thelevel] = score;

				// write file
				rapidjson::StringBuffer buffer;
				rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
				docs.Accept(writer);

				FILE* file = fopen(path.c_str(), "wb");
				if (file)
				{
					fputs(buffer.GetString(), file);
					fclose(file);
				}
			}
		}
	}
}


