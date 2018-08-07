
#pragma once

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

/*
 * MULTI-CHANNEL SIGNED DISTANCE FIELD GENERATOR v1.5 (2017-07-23)
 * ---------------------------------------------------------------
 * A utility by Viktor Chlumsky, (c) 2014 - 2017
 *
 * The technique used to generate multi-channel distance fields in this code
 * has been developed by Viktor Chlumsky in 2014 for his master's thesis,
 * "Shape Decomposition for Multi-Channel Distance Fields". It provides improved
 * quality of sharp corners in glyphs and other 2D shapes in comparison to monochrome
 * distance fields. To reconstruct an image of the shape, apply the median of three
 * operation on the triplet of sampled distance field values.
 *
 */

#include "core/arithmetics.hpp"
#include "core/Vector2.h"
#include "core/Shape.h"
#include "core/Bitmap.h"
#include "core/edge-coloring.h"
#include "core/render-sdf.h"
#include "core/save-bmp.h"
#include "core/shape-description.h"

#define MSDFGEN_VERSION "1.5"

namespace msdfgen {

/// Generates a conventional single-channel signed distance field.
void generateSDF(Bitmap<float> &output, const Shape &shape, double range, const Vector2 &scale, const Vector2 &translate);

/// Generates a single-channel signed pseudo-distance field.
void generatePseudoSDF(Bitmap<float> &output, const Shape &shape, double range, const Vector2 &scale, const Vector2 &translate);

/// Generates a multi-channel signed distance field. Edge colors must be assigned first! (see edgeColoringSimple)
void generateMSDF(Bitmap<FloatRGB> &output, const Shape &shape, double range, const Vector2 &scale, const Vector2 &translate, double edgeThreshold = 1.00000001);

// Original simpler versions of the previous functions, which work well under normal circumstances, but cannot deal with overlapping contours.
void generateSDF_legacy(Bitmap<float> &output, const Shape &shape, double range, const Vector2 &scale, const Vector2 &translate);
void generatePseudoSDF_legacy(Bitmap<float> &output, const Shape &shape, double range, const Vector2 &scale, const Vector2 &translate);
void generateMSDF_legacy(Bitmap<FloatRGB> &output, const Shape &shape, double range, const Vector2 &scale, const Vector2 &translate, double edgeThreshold = 1.00000001);

}

extern "C" {

struct Element {
    int32_t type;
    float x, y, x1, y1;
};

struct Bounds {
    float minX, minY, maxX, maxY;
};

EXPORT_API const char * createMsdfTexture(float *data, int width, int height, msdfgen::Vector2 translation, double pxRange, const msdfgen::Vector2 scale, const Element * elements, size_t elementCount, Bounds bounds);

}
