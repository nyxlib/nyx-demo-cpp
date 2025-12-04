/*--------------------------------------------------------------------------------------------------------------------*/

#include <cstdlib>

#include "../include/device_demo.hpp"

/*--------------------------------------------------------------------------------------------------------------------*/

namespace nyx_nyx_demo {

/*--------------------------------------------------------------------------------------------------------------------*/
/* HELPERS                                                                                                            */
/*--------------------------------------------------------------------------------------------------------------------*/

static void gen_noise(float *dst, size_t n, float mean_db)
{
    for(size_t i = 0; i < n; i++)
    {
        float u = (float) std::rand() / (float) RAND_MAX; // NOLINT(*-msc50-cpp)
        float v = (float) std::rand() / (float) RAND_MAX; // NOLINT(*-msc50-cpp)

        float w = (u + v - 1.0f) * 6.0f;

        dst[i] = mean_db + w;
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

static void gen_delta(float *dst, size_t n, float mean_db)
{
    gen_noise(dst, n, mean_db);

    dst[n / 2U] += 20.0f;
}

/*--------------------------------------------------------------------------------------------------------------------*/

static void gen_comb(float *dst, size_t n, float mean_db)
{
    gen_noise(dst, n, mean_db);

    size_t step = n / 8u;

    for(size_t i = step / 2u; i < n; i += step)
    {
        dst[i] += 20.0f;
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
/* DEVICE                                                                                                             */
/*--------------------------------------------------------------------------------------------------------------------*/

DeviceDemo::DeviceDemo()
{
    this->glueInitialize();
}

/*--------------------------------------------------------------------------------------------------------------------*/

void DeviceDemo::initialize(nyx_node_t *node)
{
    nyx_node_add_timer(node, 50, +[](void *arg) {

        DeviceDemo *that = static_cast<DeviceDemo *>(arg);

        if(that->s_run != NYX_ONOFF_ON)
        {
            return;
        }

        /*------------------------------------------------------------------------------------------------------------*/

        static float spectrum[4096];

        const size_t n = (that->s_fft_size <= 4096U) ? (size_t) that->s_fft_size
                                                     : (size_t) 4096U
        ;

        switch(that->s_mode)
        {
            case DEMO_MODE_NOISE: gen_noise(spectrum, n, that->s_power); break;
            case DEMO_MODE_DELTA: gen_delta(spectrum, n, that->s_power); break;
            default:              gen_comb(spectrum, n, that->s_power); break;
        }

        /*------------------------------------------------------------------------------------------------------------*/

        size_t sizes[] = {sizeof(that->s_samp_rate), sizeof(that->s_frequency), n * sizeof(float)};
        BUFF_t buffs[] = {&that->s_samp_rate       , &that->s_frequency       , spectrum         };

        nyx_stream_pub(that->vector_spectrum, 100, sizes, buffs);

        /*------------------------------------------------------------------------------------------------------------*/

    }, this);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void DeviceDemo::finalize(nyx_node_t *node)
{
    /* TO BE IMPLEMENTED */
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool DeviceDemo::onRunRunChanged(nyx_dict_t *vector, nyx_dict_t *def, int newValue, int oldValue)
{
    this->s_run = (nyx_onoff_t) newValue;

    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool DeviceDemo::onSignalModeModeNoiseChanged(nyx_dict_t *vector, nyx_dict_t *def, int newValue, int oldValue)
{
    if(newValue == NYX_ONOFF_ON)
    {
        this->s_mode = DEMO_MODE_NOISE;
    }

    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool DeviceDemo::onSignalModeModeDeltaChanged(nyx_dict_t *vector, nyx_dict_t *def, int newValue, int oldValue)
{
    if(newValue == NYX_ONOFF_ON)
    {
        this->s_mode = DEMO_MODE_DELTA;
    }

    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool DeviceDemo::onSignalModeModeCombChanged(nyx_dict_t *vector, nyx_dict_t *def, int newValue, int oldValue)
{
    if(newValue == NYX_ONOFF_ON)
    {
        this->s_mode = DEMO_MODE_COMB;
    }

    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool DeviceDemo::onSignalParamsSampRateChanged(nyx_dict_t *vector, nyx_dict_t *def, double newValue, double oldValue)
{
    this->s_samp_rate = (float) newValue;

    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool DeviceDemo::onSignalParamsFrequencyChanged(nyx_dict_t *vector, nyx_dict_t *def, double newValue, double oldValue)
{
    this->s_frequency = (float) newValue;

    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool DeviceDemo::onSignalParamsPowerChanged(nyx_dict_t *vector, nyx_dict_t *def, double newValue, double oldValue)
{
    this->s_power = (float) newValue;

    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool DeviceDemo::onFftParamsFftSizeChanged(nyx_dict_t *vector, nyx_dict_t *def, unsigned int newValue, unsigned int oldValue)
{
    this->s_fft_size = newValue;

    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

} /* namespace nyx_nyx_demo */

/*--------------------------------------------------------------------------------------------------------------------*/
