#ifndef ASSFaceError_h
#define ASSFaceError_h

#include "rx.hpp"
#include "ASSFaceCodes.h"
#include "ASSFaceEither.h"
#include "iface.h"

namespace Rx {
	using namespace rxcpp;
	using namespace rxcpp::subjects;
	using namespace rxcpp::operators;
	using namespace rxcpp::util;
}

class ASSFaceError
{
public:
	ASSFaceError();
	~ASSFaceError();
	enum ErrorFace
	{
		out = ASSFACE_EXIT,
		log = ASSFACE_LOG,
		window = ASSFACE_DIALOG,
		none = ASSFACE_OK
	};
	Rx::subject<ASSFaceEither*> errorFace;
	Rx::observable<ASSFaceEither*> observableError = errorFace.get_observable();
	void CheckError(int errorCode, ErrorFace srrorFace = ErrorFace::none);
	void CheckError(int errorCode, string message, ErrorFace srrorFace = ErrorFace::none);

private:
	Rx::subscriber<ASSFaceEither*> shootError = errorFace.get_subscriber();
	ASSFaceEither* aSFaceEither = new ASSFaceEither();
};


#endif
