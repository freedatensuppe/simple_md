#ifndef CONVERSIONFACTORS_HPP
#define CONVERSIONFACTORS_HPP

const double _AVOGADRO_NUMBER_    = 6.02214076e23;
const double _BOLTZMANN_CONSTANT_ = 1.380649e-23;   // J/K

const double _A_TO_M_ = 1e-10;

const double _AMU_TO_KG_ = 1.66053906892e-27;

const double _KCAL_TO_J_ = 4183.995381;
const double _J_TO_KCAL_ = 1 / _KCAL_TO_J_;

const double _FORCE_TO_SI_    = _KCAL_TO_J_ / _AVOGADRO_NUMBER_ / _A_TO_M_;
const double _MASS_TO_SI_     = _AMU_TO_KG_;
const double _SI_TO_VELOCITY_ = 1 / _A_TO_M_;

const double _TEMPERATURE_FACTOR_ =
    _A_TO_M_ * _A_TO_M_ * _AMU_TO_KG_ / _BOLTZMANN_CONSTANT_;

const double _E_KIN_FACTOR_ =
    _A_TO_M_ * _A_TO_M_ * _AMU_TO_KG_ * _J_TO_KCAL_ * _AVOGADRO_NUMBER_;

#endif
