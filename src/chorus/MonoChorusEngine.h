/*
    ==============================================================================
    This file is part of Tal-NoiseMaker by Patrick Kunz.

    Copyright(c) 2005-2010 Patrick Kunz, TAL
    Togu Audio Line, Inc.
    http://kunz.corrupt.ch

    This file may be licensed under the terms of of the
    GNU General Public License Version 2 (the ``GPL'').

    Software distributed under the License is distributed
    on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
    express or implied. See the GPL for the specific language
    governing rights and limitations.

    You should have received a copy of the GPL along with this
    program. If not, go to http://www.gnu.org/licenses/gpl.html
    or write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
    ==============================================================================
 */

#if !defined(__ChorusEngine_h)
#define __MonoChorusEngine_h

#include "Chorus.h"
#include "DCBlock.h"


class MonoChorusEngine
{
public:
    Chorus* chorus1;
    Chorus* chorus2;

    DCBlock* dcBlock1;
    DCBlock* dcBlock2;

    bool isChorus1Enabled;
    bool isChorus2Enabled;

    MonoChorusEngine(float sampleRate)
    {
        dcBlock1 = new DCBlock();
        dcBlock2 = new DCBlock();

        setUpChorus(sampleRate);
    }

    ~MonoChorusEngine()
    {
        delete chorus1;
        delete chorus2;
        delete dcBlock1;
        delete dcBlock2;

    }

    void setSampleRate(float sampleRate)
    {
        setUpChorus(sampleRate);
        setEnablesChorus(false, false);
    }

    void setEnablesChorus(bool isChorus1Enabled, bool isChorus2Enabled)
    {
        this->isChorus1Enabled = isChorus1Enabled;
        this->isChorus2Enabled = isChorus2Enabled;
    }

    void setUpChorus(float sampleRate)
    {
        chorus1 = new Chorus(sampleRate, 1.0f, 0.5f, 7.0f);
        chorus2 = new Chorus(sampleRate, 0.0f, 0.83f, 7.0f);
    }

    inline void process(float* sample)
    {
        float result = 0.0f;
        if (isChorus1Enabled)
        {
            result += chorus1->process(sample);
            dcBlock1->tick(&result, 0.01f);
        }
        if (isChorus2Enabled)
        {
            result += chorus2->process(sample);
            dcBlock2->tick(&result, 0.01f);
        }
        *sample = *sample + result * 1.4f;
    }
};

#endif

