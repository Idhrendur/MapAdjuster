#include "CoPoint.h"
#include "Log.h"
#include "ParserHelpers.h"

CoPoint::CoPoint(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void CoPoint::registerKeys()
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		name = commonItems::singleString(theStream).getString();
	});
	registerKeyword("source", [this](const std::string& unused, std::istream& theStream) {
		const auto coords = commonItems::intList(theStream).getInts();
		if (coords.size() == 2)
		{
			source.x = coords[0];
			source.y = coords[1];
		}
	});
	registerKeyword("target", [this](const std::string& unused, std::istream& theStream) {
		const auto coords = commonItems::intList(theStream).getInts();
		if (coords.size() == 2)
		{
			target.x = coords[0];
			target.y = coords[1];
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
