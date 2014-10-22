//
// BOMDetector.h
//

#ifndef H__BOMFILEFINDER_BOMDETECTOR__H
#define H__BOMFILEFINDER_BOMDETECTOR__H

#define NOMINMAX

#include <QString>

namespace BOMFileFinder {

class BOMDetector
{
public:
	typedef enum {
		BT_ERROR,
		BT_NONE,
		BT_UTF8,
		BT_UTF16_LE,
		BT_UTF16_BE,
		BT_UTF32_LE,
		BT_UTF32_BE,
	} bom_t;

	static bom_t detect(const QString &filename);

	static QString bomTitle(bom_t bom);
};

} // namespace BOMFileFinder

#endif // H__BOMFILEFINDER_BOMDETECTOR__H
