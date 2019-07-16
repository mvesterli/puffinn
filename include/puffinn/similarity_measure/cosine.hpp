#pragma once

#include "puffinn/format/unit_vector.hpp"
#include "puffinn/hash/simhash.hpp"
#include "puffinn/hash/crosspolytope.hpp"
#include "puffinn/math.hpp"

namespace puffinn {
    /// Measures the cosine of the angle between two unit vectors.
    /// 
    /// This is also known as the angular distance.
    /// The supported LSH families are ``CrossPolytopeHash``, ``FHTCrossPolytopeHash`` and ``SimHash``.
    struct CosineSimilarity {
        using Format = UnitVectorFormat;
        using DefaultHash = FHTCrossPolytopeHash;
        using DefaultSketch = SimHash;

        static float compute_similarity(int16_t* lhs, int16_t* rhs, unsigned int dimensions) {
            float dot = Format::from_16bit_fixed_point(
                dot_product_i16_avx2(lhs, rhs, dimensions));
            return (dot+1)/2; // Ensure the similarity is between 0 and 1.
        }
    };
}