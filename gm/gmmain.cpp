#include "SkGraphics.h"
#include "gm.h"

using namespace skiagm;

// need to explicitly declare this, or we get some weird infinite loop llist
template GMRegistry* GMRegistry::gHead;

class Iter {
public:
    Iter() {
        fReg = GMRegistry::Head();
    }
	
    GM* next() {
        if (fReg) {
            GMRegistry::Factory fact = fReg->factory();
            fReg = fReg->next();
            return fact(0);
        }
        return NULL;
    }
	
    static int Count() {
        const GMRegistry* reg = GMRegistry::Head();
        int count = 0;
        while (reg) {
            count += 1;
            reg = reg->next();
        }
        return count;
    }
	
private:
    const GMRegistry* fReg;
};

class SkAutoGraphics {
public:
    SkAutoGraphics() {
        SkGraphics::Init();
    }
    ~SkAutoGraphics() {
        SkGraphics::Term();
    }
};

static const struct {
	SkBitmap::Config	fConfig;
	bool				fUsePicture;
	const char*			fName;
} gRec[] = {
	{ SkBitmap::kARGB_8888_Config,	false,	"8888" },
	{ SkBitmap::kARGB_4444_Config,	false,	"4444" },
	{ SkBitmap::kRGB_565_Config,	false,	"565" },
	{ SkBitmap::kA8_Config,			false,	"A8" },
};

int main (int argc, char * const argv[]) {
    SkAutoGraphics ag;
    
    Iter iter;
    GM* gm;

    while ((gm = iter.next()) != NULL) {
		SkISize size = gm->getISize();
		SkDebugf("---- gm %p [%d %d]\n", gm, size.width(), size.height());
		SkBitmap bitmap;
		for (size_t i = 0; i < SK_ARRAY_COUNT(gRec); i++) {
			bitmap.setConfig(gRec[i].fConfig, size.width(), size.height());
			bitmap.allocPixels();
			bitmap.eraseColor(0);
			SkCanvas canvas(bitmap);

			SkDebugf("------- drawing to %s config\n", gRec[i].fName);
			gm->draw(&canvas);
#if 0
			if (gRec[i].fUsePicture) {
				SkPicture picture;
				gm->draw(picture.beginRecording(size.width(), size.height(), 0));
				canvas.drawPicture(picture);
			} else {
			}
#endif
		}
        SkDELETE(gm);
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////

using namespace skiagm;

GM::GM() {}
GM::~GM() {}

void GM::draw(SkCanvas* canvas) {
	this->onDraw(canvas);
}


