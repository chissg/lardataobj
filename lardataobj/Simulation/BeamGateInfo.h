// Simulation/BeamGateInfo.h
// William Seligman <seligman@nevis.columbia.edu>

// A simple model of a single beam gate signal.

#ifndef Simulation_BeamGateInfo_h
#define Simulation_BeamGateInfo_h

#include "lardataobj/Simulation/BeamTypes.h"

#include <functional> // std::less

namespace sim {

  class BeamGateInfo
  {
  public:

    // Simple constructors/destructors.
    // Units are nanoseconds (ns).
    // The default values are those of the BNB beam gate.
    BeamGateInfo( double start = 0, double width = 1600., BeamType_t type = kBNB )
      : fm_start(start)
      , fm_width(width)
      , fm_beam_type(type)
    {}

    // No "setters" for beam-gate start or width; you have to assign
    // them when you create a BeamGateInfo object.
    double Start() const { return fm_start; }
    double Width() const { return fm_width; }
    BeamType_t BeamType() const { return fm_beam_type; }


  private:
    double fm_start; // Start of the beam gate relative to the t0 of the initial simulated event window, in ns.
    double fm_width; // Width of the beam gate.
    BeamType_t fm_beam_type; ///< Type of beam

  };

  // In case we want to sort a collection of BeamGateInfos (e.g.,
  // std::set<BeamGateInfo>), here's the definition of the less-than
  // operator.
  bool operator<( const BeamGateInfo& lhs, const BeamGateInfo& rhs )
  {
    // Sort by start; in the enormously-unlikely case that two beam
    // gates (BNB and NuMI?) start at the same time, sort by width.
    if ( lhs.Start() < rhs.Start() )
      return true;
    if ( lhs.Start() == rhs.Start() )
      return ( lhs.Width() < lhs.Width() );
    return false;
  }

} // namespace sim

// For no extra charge, include how to sort BeamGateInfo*, just in
// case we want (for example) a std::set<BeamGateInfo*>.
namespace std {
  template <>
  class less<sim::BeamGateInfo*>
  {
  public:
    bool operator()( const sim::BeamGateInfo* lhs, const sim::BeamGateInfo* rhs )
    {
      return (*lhs) < (*rhs);
    }
  };
} // std

#endif // Simulation_BeamGateInfo_h
