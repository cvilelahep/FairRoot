/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of FileSink::Run() with Root TMessage transport data format

#include "Payload.h"
#include "RootSerializer.h"

template<>
void FileSink<TestDetectorTMessage>::InitTask()
{
    OnData(fInChannelName, [this](fair::mq::MessagePtr& msg, int /*index*/) {
        ++fReceivedMsgs;

        RootSerializer().Deserialize(*msg, fOutput);

        fTree.SetBranchAddress("Output", &fOutput);
        fTree.Fill();

        if (fMaxMsgs != 0) {
            if (fReceivedMsgs == fMaxMsgs) {
                return false;
            }
        }

        return true;
    });
}
