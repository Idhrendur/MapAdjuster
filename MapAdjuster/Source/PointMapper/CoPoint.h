#ifndef CO_POINT_H
#define CO_POINT_H

#include "Parser.h"

struct Point
{
	int x = 0;
	int y = 0;
};

class CoPoint: commonItems::parser
{
  public:
	CoPoint() = default;
	explicit CoPoint(std::istream& theStream);

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getSource() const { return source; }
	[[nodiscard]] const auto& getTarget() const { return target; }

  private:
	void registerKeys();

	std::string name;
	Point source;
	Point target;

};

#endif // CO_POINT_H
