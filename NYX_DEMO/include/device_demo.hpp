/*--------------------------------------------------------------------------------------------------------------------*/

#ifndef NYX_NYX_DEMO_DEMO_HPP
#define NYX_NYX_DEMO_DEMO_HPP

/*--------------------------------------------------------------------------------------------------------------------*/

#include <nyx_node.hpp>

/*--------------------------------------------------------------------------------------------------------------------*/

namespace nyx_nyx_demo {

/*--------------------------------------------------------------------------------------------------------------------*/

typedef enum demo_mode_e
{
    DEMO_MODE_NOISE = 0,
    DEMO_MODE_DELTA = 1,
    DEMO_MODE_COMB = 2,

} demo_mode_t;

/*--------------------------------------------------------------------------------------------------------------------*/

class DeviceDemo : public Nyx::BaseDevice
{
public:
    /*----------------------------------------------------------------------------------------------------------------*/

    DeviceDemo();

    /*----------------------------------------------------------------------------------------------------------------*/

    STR_t name() const override
    {
        return "Demo";
    }

    /*----------------------------------------------------------------------------------------------------------------*/

    bool onRunRunChanged(nyx_dict_t *vector, nyx_dict_t *def, int newValue, int oldValue);

    bool onSignalModeModeNoiseChanged(nyx_dict_t *vector, nyx_dict_t *def, int newValue, int oldValue);
    bool onSignalModeModeDeltaChanged(nyx_dict_t *vector, nyx_dict_t *def, int newValue, int oldValue);
    bool onSignalModeModeCombChanged(nyx_dict_t *vector, nyx_dict_t *def, int newValue, int oldValue);

    bool onSignalParamsSampRateChanged(nyx_dict_t *vector, nyx_dict_t *def, double newValue, double oldValue);
    bool onSignalParamsFrequencyChanged(nyx_dict_t *vector, nyx_dict_t *def, double newValue, double oldValue);
    bool onSignalParamsPowerChanged(nyx_dict_t *vector, nyx_dict_t *def, double newValue, double oldValue);

    bool onFftParamsFftSizeChanged(nyx_dict_t *vector, nyx_dict_t *def, unsigned int newValue, unsigned int oldValue);


    /*----------------------------------------------------------------------------------------------------------------*/

protected:
    /*----------------------------------------------------------------------------------------------------------------*/

    nyx_dict_t *vector_run_run = nullptr;
    nyx_dict_t *vector_run = nullptr;

    nyx_dict_t *vector_signal_mode_mode_noise = nullptr;
    nyx_dict_t *vector_signal_mode_mode_delta = nullptr;
    nyx_dict_t *vector_signal_mode_mode_comb = nullptr;
    nyx_dict_t *vector_signal_mode = nullptr;

    nyx_dict_t *vector_signal_params_samp_rate = nullptr;
    nyx_dict_t *vector_signal_params_frequency = nullptr;
    nyx_dict_t *vector_signal_params_power = nullptr;
    nyx_dict_t *vector_signal_params = nullptr;

    nyx_dict_t *vector_fft_params_fft_size = nullptr;
    nyx_dict_t *vector_fft_params = nullptr;

    nyx_dict_t *vector_spectrum_samp_rate = nullptr;
    nyx_dict_t *vector_spectrum_frequency = nullptr;
    nyx_dict_t *vector_spectrum_samples = nullptr;
    nyx_dict_t *vector_spectrum = nullptr;

    /*----------------------------------------------------------------------------------------------------------------*/

private:
    /*----------------------------------------------------------------------------------------------------------------*/

    void glueInitialize() override;

    void initialize(nyx_node_t *node) override;

    void finalize(nyx_node_t *node) override;

    /*----------------------------------------------------------------------------------------------------------------*/

    nyx_onoff_t s_run = NYX_ONOFF_OFF;
    demo_mode_t s_mode = DEMO_MODE_NOISE;

    float s_samp_rate = 2000000.0f;
    float s_frequency = 143050000.0f;
    float s_power = -30.0f;

    unsigned int s_fft_size = 512U;

    /*----------------------------------------------------------------------------------------------------------------*/
};

/*--------------------------------------------------------------------------------------------------------------------*/

} /* namespace nyx_nyx_demo */

/*--------------------------------------------------------------------------------------------------------------------*/

#endif /* NYX_NYX_DEMO_DEMO_HPP */

/*--------------------------------------------------------------------------------------------------------------------*/
