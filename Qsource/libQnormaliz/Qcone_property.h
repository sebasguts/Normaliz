/*
 * Normaliz
 * Copyright (C) 2007-2014  Winfried Bruns, Bogdan Ichim, Christof Soeger
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As an exception, when this program is distributed through (i) the App Store
 * by Apple Inc.; (ii) the Mac App Store by Apple Inc.; or (iii) Google Play
 * by Google Inc., then that store may impose any digital rights management,
 * device limits and/or redistribution restrictions that are required by its
 * terms of service.
 */

#ifndef QCONE_PROPERTY_H_
#define QCONE_PROPERTY_H_

#include <bitset>
#include <ostream>

namespace libQnormaliz {

/* An enumeration of things, that can be computed for a cone.
 * The namespace prevents interfering with other names.
 * Remember to change also the string conversion if you change this enum!
 */

namespace QConeProperty {
    enum Enum {
        FIRST_MATRIX,
        Generators = Enum::FIRST_MATRIX,
        ExtremeRays,
        VerticesOfPolyhedron,
        SupportHyperplanes,
        HilbertBasis,
        ModuleGenerators,
        Deg1Elements,
        ModuleGeneratorsOverOriginalMonoid,
        ExcludedFaces,
        OriginalMonoidGenerators,
        MaximalSubspace,
        Equations,
        Congruences,
        LAST_MATRIX = Enum::Congruences,
        FIRST_MATRIX_FLOAT,
        SuppHypsFloat = Enum::FIRST_MATRIX_FLOAT,
        VerticesFloat,
        LAST_MATRIX_FLOAT = Enum::VerticesFloat,
        // Vector values
        FIRST_VECTOR,
        Grading = Enum::FIRST_VECTOR,
        Dehomogenization,
        WitnessNotIntegrallyClosed,
        GeneratorOfInterior,
        ClassGroup,
        LAST_VECTOR = Enum::ClassGroup,
        // Integer valued,
        FIRST_INTEGER,
        TriangulationDetSum = Enum::FIRST_INTEGER,
        ReesPrimaryMultiplicity,
        GradingDenom,
        UnitGroupIndex,
        InternalIndex,
        LAST_INTEGER = Enum::InternalIndex,
        FIRST_GMP_INTEGER,
        ExternalIndex = FIRST_GMP_INTEGER,
        LAST_GMP_INTEGER = Enum::ExternalIndex,
        // rational valued
        FIRST_RATIONAL,
        Multiplicity = Enum::FIRST_RATIONAL,
        Volume,
        Integral,
        VirtualMultiplicity,
        LAST_RATIONAL = Enum::VirtualMultiplicity,
        // floating point valued
        FIRST_FLOAT,
        EuclideanVolume = Enum::FIRST_FLOAT,
        LAST_FLOAT = Enum::EuclideanVolume,
        // dimensions
        FIRST_MACHINE_INTEGER,
        TriangulationSize = Enum::FIRST_MACHINE_INTEGER,
        RecessionRank,
        AffineDim,
        ModuleRank,
        Rank,
        EmbeddingDim,
        LAST_MACHINE_INTEGER = Enum::EmbeddingDim,
        // boolean valued 
        FIRST_BOOLEAN,
        IsPointed = Enum::FIRST_BOOLEAN,
        IsDeg1ExtremeRays,
        IsDeg1HilbertBasis,
        IsIntegrallyClosed,
        IsReesPrimary,
        IsInhomogeneous,
        IsGorenstein,
        LAST_BOOLEAN = Enum::IsGorenstein,
        // complex structures
        FIRST_COMPLEX_STRUCTURE,
        Triangulation = Enum::FIRST_COMPLEX_STRUCTURE,
        StanleyDec,
        InclusionExclusionData,
        IntegerHull,
        ProjectCone,
        ConeDecomposition,
        HilbertSeries,
        HilbertQuasiPolynomial,
        EhrhartSeries,
        WeightedEhrhartSeries,
        WeightedEhrhartQuasiPolynomial,
        Sublattice,
        LAST_COMPLEX_STRUCTURE = Enum::Sublattice,
        //
        // integer type for computations
        //
        FIRST_PROPERTY,
        BigInt = Enum::FIRST_PROPERTY,
        //
        // algorithmic variants
        //
        DefaultMode,
        Approximate,
        BottomDecomposition,
        NoBottomDec,       
        DualMode,
        PrimalMode,
        Projection,
        ProjectionFloat,
        NoProjection,
        Symmetrize,
        NoSymmetrization,
        NoSubdivision,
        NoNestedTri, // synonym for NoSubdivision
        KeepOrder,
        HSOP,
        NoPeriodBound,
        SCIP,
        NoLLL,
        NoRelax,
        Descent,
        NoDescent,
        //
        // checking properties of already computed data
        // (cannot be used as a computation goal)
        //
        IsTriangulationNested,
        IsTriangulationPartial,
        //
        // ONLY FOR INTERNAL CONTROL
        //
        ExplicitHilbertSeries,
        NakedDual,
        EnumSize,
        LAST_PROPERTY = Enum::EnumSize // this has to be the last entry, to get the number of entries in the enum
    }; // remember to change also the string conversion function if you change this enum
}

namespace QOutputType{
    enum Enum {
        Matrix,
        MatrixFloat,
        Vector,
        Integer,
        GMPInteger,
        Rational,
        Float,
        MachineInteger,
        Bool,
        Complex,
        Void
    };
}

class ConeProperties {
public:
    /* Constructors */
    ConeProperties();
    ConeProperties(QConeProperty::Enum);
    ConeProperties(QConeProperty::Enum, QConeProperty::Enum);
    ConeProperties(QConeProperty::Enum, QConeProperty::Enum, QConeProperty::Enum);
    ConeProperties(const std::bitset<QConeProperty::EnumSize>&);

    /* set properties */
    ConeProperties& set(QConeProperty::Enum, bool value=true);
    ConeProperties& set(const std::string s, bool value=true);
    ConeProperties& set(QConeProperty::Enum, QConeProperty::Enum);
    ConeProperties& set(QConeProperty::Enum, QConeProperty::Enum, QConeProperty::Enum);
    ConeProperties& set(const ConeProperties&);

    /* reset (=unset) properties */
    ConeProperties& reset(QConeProperty::Enum Property);
    ConeProperties& reset(const ConeProperties&);
    ConeProperties& reset_compute_options();

    /* test which/how many properties are set */
    bool test(QConeProperty::Enum Property) const;
    bool any() const;
    bool none() const;
    size_t count () const;

    /* return the restriction of this to the goals / options */
    ConeProperties goals();
    ConeProperties options();

    /* the following methods are used internally */
    void set_preconditions(bool inhomogeneous);    // activate properties which are needed implicitly
    void prepare_compute_options(bool inhomogeneous);
    void check_sanity(bool inhomogeneous);
    void check_Q_permissible();

    /* print it in a nice way */
    friend std::ostream& operator<<(std::ostream&, const ConeProperties&);


private:
    std::bitset<QConeProperty::EnumSize> CPs;

};

// conversion to/from strings
bool isConeProperty(QConeProperty::Enum& cp, const std::string& s);
QConeProperty::Enum toConeProperty(const std::string&);
const std::string& toString(QConeProperty::Enum);
std::ostream& operator<<(std::ostream&, const ConeProperties&);

}

#endif /* CONE_PROPERTY_H_ */
