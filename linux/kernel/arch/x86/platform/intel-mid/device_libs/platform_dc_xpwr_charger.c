
#include <linux/gpio.h>
#include <asm/intel-mid.h>
#include <linux/lnw_gpio.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/power/dc_xpwr_charger.h>
#include <asm/intel_em_config.h>

static struct dollarcove_chrg_pdata pdata;

#ifdef CONFIG_POWER_SUPPLY_CHARGER
#define DC_CHRG_CHRG_CUR_NOLIMIT	1800
#define DC_CHRG_CHRG_CUR_MEDIUM		1400
#define DC_CHRG_CHRG_CUR_LOW		1000

static struct ps_batt_chg_prof ps_batt_chrg_prof;
static struct ps_pse_mod_prof batt_chg_profile;
static struct power_supply_throttle dc_chrg_throttle_states[] = {
	{
		.throttle_action = PSY_THROTTLE_CC_LIMIT,
		.throttle_val = DC_CHRG_CHRG_CUR_NOLIMIT,
	},
	{
		.throttle_action = PSY_THROTTLE_CC_LIMIT,
		.throttle_val = DC_CHRG_CHRG_CUR_MEDIUM,
	},
	{
		.throttle_action = PSY_THROTTLE_CC_LIMIT,
		.throttle_val = DC_CHRG_CHRG_CUR_LOW,
	},
	{
		.throttle_action = PSY_THROTTLE_DISABLE_CHARGING,
	},
};

static char *dc_chrg_supplied_to[] = {
	"dollar_cove_battery"
};

static void *platform_debug_batt_charge_profile(void)
{
	struct ps_temp_chg_table temp_mon_range[BATT_TEMP_NR_RNG];

	char batt_str[] = "INTN0001";

	memcpy(batt_chg_profile.batt_id, batt_str, strlen(batt_str));

#ifdef CONFIG_BATTERY_TYPE
#if defined(CONFIG_BATTERY_BT_B0BFQ)
	batt_chg_profile.battery_type = 0x2;
	batt_chg_profile.capacity = 7135;
	batt_chg_profile.voltage_max = 4200;
	batt_chg_profile.chrg_term_ma = 250;
	batt_chg_profile.low_batt_mV = 3400;
	batt_chg_profile.disch_tmp_ul = 52;
	batt_chg_profile.disch_tmp_ll = -5;
	batt_chg_profile.temp_mon_ranges = 3;

	temp_mon_range[0].temp_up_lim = 52;
	temp_mon_range[0].full_chrg_vol = 4200;
	temp_mon_range[0].full_chrg_cur = 1800;
	temp_mon_range[0].maint_chrg_vol_ll = 4100;
	temp_mon_range[0].maint_chrg_vol_ul = 4200;
	temp_mon_range[0].maint_chrg_cur = 1800;

	temp_mon_range[1].temp_up_lim = 23;
	temp_mon_range[1].full_chrg_vol = 4200;
	temp_mon_range[1].full_chrg_cur = 1000;
	temp_mon_range[1].maint_chrg_vol_ll = 4100;
	temp_mon_range[1].maint_chrg_vol_ul = 4200;
	temp_mon_range[1].maint_chrg_cur = 1000;

	temp_mon_range[2].temp_up_lim = 10;
	temp_mon_range[2].full_chrg_vol = 4200;
	temp_mon_range[2].full_chrg_cur = 500;
	temp_mon_range[2].maint_chrg_vol_ll = 4100;
	temp_mon_range[2].maint_chrg_vol_ul = 4200;
	temp_mon_range[2].maint_chrg_cur = 500;

	memcpy(batt_chg_profile.temp_mon_range,
		temp_mon_range,
		BATT_TEMP_NR_RNG * sizeof(struct ps_temp_chg_table));

	batt_chg_profile.temp_low_lim = -5;
	ps_batt_chrg_prof.chrg_prof_type = PSE_MOD_CHRG_PROF;
#elif defined(CONFIG_BATTERY_BT_E002H)
	batt_chg_profile.battery_type = 0x2;
	batt_chg_profile.capacity = 5130;
	batt_chg_profile.voltage_max = 4350;
	batt_chg_profile.chrg_term_ma = 250;
	batt_chg_profile.low_batt_mV = 3400;
	batt_chg_profile.disch_tmp_ul = 46;
	batt_chg_profile.disch_tmp_ll = 0;
	batt_chg_profile.temp_mon_ranges = 6;

	temp_mon_range[0].temp_up_lim = 46;
	temp_mon_range[0].full_chrg_vol = 4350;
	temp_mon_range[0].full_chrg_cur = 400;
	temp_mon_range[0].maint_chrg_vol_ll = 4285;
	temp_mon_range[0].maint_chrg_vol_ul = 4350;
	temp_mon_range[0].maint_chrg_cur = 400;

	temp_mon_range[1].temp_up_lim = 44;
	temp_mon_range[1].full_chrg_vol = 4350;
	temp_mon_range[1].full_chrg_cur = 800;
	temp_mon_range[1].maint_chrg_vol_ll = 4285;
	temp_mon_range[1].maint_chrg_vol_ul = 4350;
	temp_mon_range[1].maint_chrg_cur = 800;

	temp_mon_range[2].temp_up_lim = 42;
	temp_mon_range[2].full_chrg_vol = 4350;
	temp_mon_range[2].full_chrg_cur = 1200;
	temp_mon_range[2].maint_chrg_vol_ll = 4285;
	temp_mon_range[2].maint_chrg_vol_ul = 4350;
	temp_mon_range[2].maint_chrg_cur = 1200;

	temp_mon_range[3].temp_up_lim = 40;
	temp_mon_range[3].full_chrg_vol = 4350;
	temp_mon_range[3].full_chrg_cur = 1600;
	temp_mon_range[3].maint_chrg_vol_ll = 4285;
	temp_mon_range[3].maint_chrg_vol_ul = 4350;
	temp_mon_range[3].maint_chrg_cur = 1600;

	temp_mon_range[4].temp_up_lim = 25;
	temp_mon_range[4].full_chrg_vol = 4350;
	temp_mon_range[4].full_chrg_cur = 800;
	temp_mon_range[4].maint_chrg_vol_ll = 4285;
	temp_mon_range[4].maint_chrg_vol_ul = 4350;
	temp_mon_range[4].maint_chrg_cur = 800;

	temp_mon_range[5].temp_up_lim = 10;
	temp_mon_range[5].full_chrg_vol = 4350;
	temp_mon_range[5].full_chrg_cur = 400;
	temp_mon_range[5].maint_chrg_vol_ll = 4285;
	temp_mon_range[5].maint_chrg_vol_ul = 4350;
	temp_mon_range[5].maint_chrg_cur = 400;

	memcpy(batt_chg_profile.temp_mon_range,
		temp_mon_range,
		BATT_TEMP_NR_RNG * sizeof(struct ps_temp_chg_table));

	batt_chg_profile.temp_low_lim = 0;
	ps_batt_chrg_prof.chrg_prof_type = PSE_MOD_CHRG_PROF;
#endif
#else
	batt_chg_profile.battery_type = 0x2;
	batt_chg_profile.capacity = 5130;
	batt_chg_profile.voltage_max = 4350;
	batt_chg_profile.chrg_term_ma = 250;
	batt_chg_profile.low_batt_mV = 3400;
	batt_chg_profile.disch_tmp_ul = 45;
	batt_chg_profile.disch_tmp_ll = 0;
	batt_chg_profile.temp_mon_ranges = 3;

	temp_mon_range[0].temp_up_lim = 45;
	temp_mon_range[0].full_chrg_vol = 4350;
	temp_mon_range[0].full_chrg_cur = 1800;
	temp_mon_range[0].maint_chrg_vol_ll = 4285;
	temp_mon_range[0].maint_chrg_vol_ul = 4350;
	temp_mon_range[0].maint_chrg_cur = 1800;

	temp_mon_range[1].temp_up_lim = 23;
	temp_mon_range[1].full_chrg_vol = 4350;
	temp_mon_range[1].full_chrg_cur = 1000;
	temp_mon_range[1].maint_chrg_vol_ll = 4285;
	temp_mon_range[1].maint_chrg_vol_ul = 4350;
	temp_mon_range[1].maint_chrg_cur = 1000;

	temp_mon_range[2].temp_up_lim = 10;
	temp_mon_range[2].full_chrg_vol = 4350;
	temp_mon_range[2].full_chrg_cur = 500;
	temp_mon_range[2].maint_chrg_vol_ll = 4285;
	temp_mon_range[2].maint_chrg_vol_ul = 4350;
	temp_mon_range[2].maint_chrg_cur = 500;

	memcpy(batt_chg_profile.temp_mon_range,
		temp_mon_range,
		BATT_TEMP_NR_RNG * sizeof(struct ps_temp_chg_table));

	batt_chg_profile.temp_low_lim = 0;
	ps_batt_chrg_prof.chrg_prof_type = PSE_MOD_CHRG_PROF;
#endif
}

static void *platform_get_batt_charge_profile(void)
{
	if (!em_config_get_charge_profile(&batt_chg_profile))
		ps_batt_chrg_prof.chrg_prof_type = CHRG_PROF_NONE;
	else
		ps_batt_chrg_prof.chrg_prof_type = PSE_MOD_CHRG_PROF;

/*Reserve for debug--Set batt charge profile without em*/
/*1: enable debug set*/
/*0: disable debug set*/
#if 1
	platform_debug_batt_charge_profile();
#endif

	ps_batt_chrg_prof.batt_prof = &batt_chg_profile;
	battery_prop_changed(POWER_SUPPLY_BATTERY_INSERTED,
			&ps_batt_chrg_prof);

	return &ps_batt_chrg_prof;
}

static void platform_init_chrg_params(struct dollarcove_chrg_pdata *pdata)
{
	pdata->throttle_states = dc_chrg_throttle_states;
	pdata->supplied_to = dc_chrg_supplied_to;
	pdata->num_throttle_states = ARRAY_SIZE(dc_chrg_throttle_states);
	pdata->num_supplicants = ARRAY_SIZE(dc_chrg_supplied_to);
	pdata->supported_cables = POWER_SUPPLY_CHARGER_TYPE_USB;
	pdata->chg_profile = (struct ps_batt_chg_prof *)
			platform_get_batt_charge_profile();
}
#endif

static void *get_platform_data(void)
{
	int ret;

#ifdef CONFIG_BATTERY_TYPE
#if defined(CONFIG_BATTERY_BT_B0BFQ)
	pdata.max_cc = 2000;
	pdata.max_cv = 4200;
	pdata.def_cc = 500;
	pdata.def_cv = 4200;
	pdata.def_ilim = 900;
	pdata.def_iterm = 300;
	pdata.def_max_temp = 52;
	pdata.def_min_temp = -5;
#elif defined(CONFIG_BATTERY_BT_E002H)
	pdata.max_cc = 1600;
	pdata.max_cv = 4350;
	pdata.def_cc = 500;
	pdata.def_cv = 4350;
	pdata.def_ilim = 900;
	pdata.def_iterm = 250;
	pdata.def_max_temp = 46;
	pdata.def_min_temp = 0;
#endif
#else
	pdata.max_cc = 2000;
	pdata.max_cv = 4350;
	pdata.def_cc = 500;
	pdata.def_cv = 4350;
	pdata.def_ilim = 900;
	pdata.def_iterm = 300;
	pdata.def_max_temp = 55;
	pdata.def_min_temp = 0;
#endif
	pdata.otg_gpio = 117; /* GPIONC_15 */
	/* configure output */
	ret = gpio_request(pdata.otg_gpio, "otg_gpio");
	if (ret) {
		pr_err("unable to request GPIO pin\n");
		pdata.otg_gpio = -1;
	} else {
		lnw_gpio_set_alt(pdata.otg_gpio, 0);
	}

	platform_init_chrg_params(&pdata);
	return &pdata;
}

void *dollarcove_chrg_pdata(void *info)
{
	return get_platform_data();
}
