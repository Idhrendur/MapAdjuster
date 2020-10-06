#include "PointMapper.h"
#include "Magick++.h"
#include "ParserHelpers.h"
#include <fstream>

PointMapper::PointMapper(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

PointMapper::PointMapper()
{
	coPoints = std::make_shared<std::vector<std::shared_ptr<CoPoint>>>();
	registerKeys();
	parseFile("test_mappings.txt");
	clearRegisteredKeywords();
}

void PointMapper::registerKeys()
{
	registerKeyword("link", [this](const std::string& unused, std::istream& theStream) {
		const auto coPoint = std::make_shared<CoPoint>(theStream);
		coPoints->push_back(coPoint);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}

void PointMapper::exportPoints() const
{
	std::ofstream pointFile("test_mappings.txt");
	for (const auto& coPoint: *coPoints)
		pointFile << *coPoint;
	pointFile.close();
}

void PointMapper::exportAdjustedMap() const
{
	Magick::Image sourceMap("test-from/provinces.bmp");
	
	std::vector<double> transformationVector;
	for (const auto& coPoint : *coPoints)
	{
		if (coPoint->getSource() && coPoint->getTarget())
		{
			transformationVector.emplace_back(coPoint->getSource()->x);
			transformationVector.emplace_back(coPoint->getSource()->y);
			transformationVector.emplace_back(coPoint->getTarget()->x);
			transformationVector.emplace_back(coPoint->getTarget()->y);
		}
	}
	double* theArray = &transformationVector[0];
	sourceMap.distort(MagickCore::ShepardsDistortion, transformationVector.size(), theArray, true);
	sourceMap.write("transformed.bmp");
}
