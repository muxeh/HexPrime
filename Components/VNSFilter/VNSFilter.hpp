// ======================================================================
// \title  VNSFilter.hpp
// \author maxbinaei
// \brief  hpp file for VNSFilter component implementation class
// ======================================================================

#ifndef Components_VNSFilter_HPP
#define Components_VNSFilter_HPP

#include "Components/VNSFilter/VNSFilterComponentAc.hpp"

namespace Components {

  class VNSFilter :
    public VNSFilterComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct VNSFilter object
      VNSFilter(
          const char* const compName //!< The component name
      );

      //! Destroy VNSFilter object
      ~VNSFilter();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for run
      //!
      //! Cyclical rate group call
      void run_handler(
          FwIndexType portNum, //!< The port number
          U32 context //!< The call order
      ) override;

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command TODO_1
      //!
      //! TODO
      void TODO_1_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;

      //! Handler implementation for command TODO_2
      //!
      //! TODO
      void TODO_2_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;

  };

}

#endif
