#include "BOMFileFinder/BOMDetector.h"

#include <QFile>
#include <QDataStream>

namespace BOMFileFinder {

BOMDetector::bom_t BOMDetector::detect(const QString &filename)
{
	try
	{
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly))
			return BT_ERROR;

		if (file.size() < 4)
			return BT_NONE;

		QDataStream str(&file);
		quint8 b1, b2, b3, b4;
		str >> b1 >> b2 >> b3 >> b4;

		// http://stackoverflow.com/questions/9103294/c-how-to-inspect-file-byte-order-mark-in-order-to-get-if-it-is-utf-8
		if (b1 == 0xef && b2 == 0xbb && b3 == 0xbf)
			return BT_UTF8;
		if (b1 == 0xff && b2 == 0xfe && b3 != 0 && b4 != 0)
			return BT_UTF16_LE;
		if (b1 == 0xfe && b2 == 0xff)
			return BT_UTF16_BE;
		if (b1 == 0xff && b2 == 0xfe && b3 == 0 && b4 == 0)
			return BT_UTF32_LE;
		if (b1 == 0 && b2 == 0 && b3 == 0xfe && b4 == 0xff)
			return BT_UTF32_BE;
	}
	catch (std::exception &e)
	{
		return BT_ERROR;
	}

	return BT_NONE;
}

QString BOMDetector::bomTitle(BOMDetector::bom_t bom)
{
	switch (bom)
	{
	case BT_ERROR: return "ERROR";
	case BT_NONE: return "NONE";
	case BT_UTF8: return "UTF8";
	case BT_UTF16_LE: return "UTF16_LE";
	case BT_UTF16_BE: return "UTF16_BE";
	case BT_UTF32_LE: return "UTF32_LE";
	case BT_UTF32_BE: return "UTF32_BE";
	}
	return "UNKNOWN";
}



} // namespace AppStatsD