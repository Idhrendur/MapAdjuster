#include "PointMapper.h"
#include "Log.h"
#include "ParserHelpers.h"

PointMapper::PointMapper(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

PointMapper::PointMapper()
{
	registerKeys();
	parseFile("test_mappings.txt");
	clearRegisteredKeywords();
}

void PointMapper::registerKeys()
{
	registerKeyword("link", [this](const std::string& unused, std::istream& theStream) {
		const CoPoint coPoint(theStream);
		coPoints.push_back(coPoint);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
