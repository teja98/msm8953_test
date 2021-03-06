/*
 *  drivers/cpufreq/cpufreq_elementalx.c
 *
 *  Copyright (C)  2001 Russell King
 *            (C)  2003 Venkatesh Pallipadi <venkatesh.pallipadi@intel.com>
 *                      Jun Nakajima <jun.nakajima@intel.com>
 *            (C)  2015 Aaron Segaert <asegaert@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/slab.h>
#include "cpufreq_governor.h"

/* elementalx governor macros */
#define DEF_FREQUENCY_UP_THRESHOLD		(90)
#define DEF_FREQUENCY_DOWN_DIFFERENTIAL		(20)
#define DEF_ACTIVE_FLOOR_FREQ			(960000)
#define MIN_SAMPLING_RATE			(10000)
#define DEF_SAMPLING_DOWN_FACTOR		(4)
#define MAX_SAMPLING_DOWN_FACTOR		(20)
#define FREQ_NEED_BURST(x)			(x < 800000 ? 1 : 0)
#define MAX(x,y)				(x > y ? x : y)
#define MIN(x,y)				(x < y ? x : y)
#define TABLE_SIZE				12
#define TABLE_NUM				6

static DEFINE_PER_CPU(struct ex_cpu_dbs_info_s, ex_cpu_dbs_info);

static unsigned int up_threshold_level[2] __read_mostly = {95, 85};
 
static struct ex_governor_data {
#define DEF_INPUT_EVENT_TIMEOUT			(300)
#define DEF_GBOOST_MIN_FREQ			(1574400)
#define DEF_MAX_SCREEN_OFF_FREQ			(1728000)
#define MIN_SAMPLING_RATE			(10000)
#define FREQ_NEED_BURST(x)			(x < 800000 ? 1 : 0)
#define MAX(x,y)				(x > y ? x : y)
#define MIN(x,y)				(x < y ? x : y)

static DEFINE_PER_CPU(struct ex_cpu_dbs_info_s, ex_cpu_dbs_info);

static unsigned int up_threshold_level[2] __read_mostly = {95, 85};

static struct ex_governor_data {
	bool input_event_boost;
	unsigned long input_event_boost_expired;
	unsigned int input_event_timeout;
	unsigned int input_min_freq;
	unsigned int active_floor_freq;
	unsigned int prev_load;
} ex_data = {
	.active_floor_freq = DEF_ACTIVE_FLOOR_FREQ,
	.prev_load = 0,
};


static int input_event_boosted(int cpu)
{
	if (ex_data.input_event_boost) {
		if (time_before(jiffies, ex_data.input_event_boost_expired)) {
	unsigned long flags;

	spin_lock_irqsave(&ex_data.input_boost_lock, flags);
	if (ex_data.input_event_boost) {
		if (time_before(jiffies, ex_data.input_event_boost_expired)) {
	struct ex_cpu_dbs_info_s *dbs_info = &per_cpu(ex_cpu_dbs_info, cpu);

	if (dbs_info->input_event_boost) {
		if (time_before(jiffies, dbs_info->input_event_boost_expired)) {
			return 1;
		}
		dbs_info->input_event_boost = false;
	}

	return 0;
}

static inline unsigned int ex_freq_increase(struct cpufreq_policy *p, unsigned int freq, int cpu)
static void dbs_init_freq_map_table(void)
{
	unsigned int min_diff, top1, top2;
	int cnt, i, j;
	struct cpufreq_policy *policy;

	policy = cpufreq_cpu_get(0);
	tbl = cpufreq_frequency_get_table(0);
	min_diff = policy->cpuinfo.max_freq;

	for (cnt = 0; (tbl[cnt].frequency != CPUFREQ_TABLE_END); cnt++) {
		if (cnt > 0)
			min_diff = MIN(tbl[cnt].frequency - tbl[cnt-1].frequency, min_diff);
	}

	top1 = (policy->cpuinfo.max_freq + policy->cpuinfo.min_freq) / 2;
	top2 = (policy->cpuinfo.max_freq + top1) / 2;

	for (i = 0; i < TABLE_SIZE; i++) {
		tblmap[i] = kmalloc(sizeof(unsigned int) * cnt, GFP_KERNEL);
		BUG_ON(!tblmap[i]);
		for (j = 0; j < cnt; j++)
			tblmap[i][j] = tbl[j].frequency;
	}

	for (j = 0; j < cnt; j++) {
		if (tbl[j].frequency < top1) {
			tblmap[0][j] += MAX((top1 - tbl[j].frequency)/3, min_diff);
		}

		if (tbl[j].frequency < top2) {
			tblmap[1][j] += MAX((top2 - tbl[j].frequency)/3, min_diff);
			tblmap[2][j] += MAX(((top2 - tbl[j].frequency)*2)/5, min_diff);
			tblmap[3][j] += MAX((top2 - tbl[j].frequency)/2, min_diff);
		} else {
			tblmap[3][j] += MAX((policy->cpuinfo.max_freq - tbl[j].frequency)/3, min_diff);
		}

		tblmap[4][j] += MAX((policy->cpuinfo.max_freq - tbl[j].frequency)/2, min_diff);
	}

	tbl_select[0] = 0;
	tbl_select[1] = 1;
	tbl_select[2] = 2;
	tbl_select[3] = 4;
}

static void dbs_deinit_freq_map_table(void)
{
	int i;

	if (!tbl)
		return;
static unsigned int tblmap1[TABLE_SIZE] __read_mostly = {
	616400,
	757200,
	840000,
	960000,
	1248000,
	1344000,
	1478400,
	1555200,
	1632000,
	1728000,
	1824000,
	1958400,
};

static unsigned int tblmap2[TABLE_SIZE] __read_mostly = {
	773040,
	899760,
	1014960,
	1072560,
	1248000,
	1344000,
	1478400,
	1555200,
	1632000,
	1728000,
	1824000,
	1958400,
};
static unsigned int tblmap[TABLE_NUM][TABLE_SIZE] __read_mostly = {

	//table 0
	{
		616400,
		757200,
		840000,
		960000,
		1248000,
		1344000,
		1478400,
		1555200,
		1632000,
		1728000,
		1824000,
		1958400,
	},

	//table 1
	{
		773040,
		899760,
		1014960,
		1072560,
		1248000,
		1344000,
		1478400,
		1555200,
		1632000,
		1728000,
		1824000,
		1958400,
	},

	//table 2
	{
		851100,
		956700,
		1052700,
		1100700,
		1350400,
		1416000,
		1550400,
		1627200,
		1740800,
		1824000,
		1920000,
		2054400,
	},

	//table 3
	{
		616400,
		757200,
		840000,
		960000,
		1248000,
		1344000,
		1478400,
		1555200,
		1555200,
		1555200,
		1555200,
		1555200,
	},

	//table 4
	{
		773040,
		899760,
		1014960,
		1072560,
		1248000,
		1344000,
		1478400,
		1555200,
		1555200,
		1555200,
		1555200,
		1555200,
	},

	//table 5
	{
		851100,
		956700,
		1052700,
		1100700,
		1350400,
		1416000,
		1550400,
		1627200,
		1627200,
		1627200,
		1627200,
		1627200,
	}

};

static inline int get_cpu_freq_index(unsigned int freq, struct dbs_data *dbs_data)
{
	static int saved_index = 0;
	int index;
	
	if (!dbs_data->freq_table) {
		pr_warn("tbl is NULL, use previous value %d\n", saved_index);
		return saved_index;
	}

	for (index = 0; (dbs_data->freq_table[index].frequency != CPUFREQ_TABLE_END); index++) {
		if (dbs_data->freq_table[index].frequency >= freq) {
			saved_index = index;
			break;
		}
	}

	return index;
}

static inline unsigned int ex_freq_increase(struct cpufreq_policy *p, unsigned int freq)
{
	if (freq > p->max) {
		return p->max;
	} 
	
	return freq;
static void freq_increase(struct cpufreq_policy *p, unsigned int freq)
{
	if (freq > p->max) {
		return p->max;
	} 
	
	else if (input_event_boosted() || ex_data.g_count > 30) {
		freq = MAX(freq, ex_data.input_min_freq);
	} 

	else if (ex_data.suspended) {
		freq = MIN(freq, ex_data.max_screen_off_freq);
	}

	return freq;
}

static void ex_check_cpu(int cpu, unsigned int load)
{
	struct ex_cpu_dbs_info_s *dbs_info = &per_cpu(ex_cpu_dbs_info, cpu);
	struct cpufreq_policy *policy = dbs_info->cdbs.cur_policy;
	struct dbs_data *dbs_data = policy->governor_data;
	struct ex_dbs_tuners *ex_tuners = dbs_data->tuners;
	unsigned int max_load_freq = 0, freq_next = 0;
	unsigned int j, avg_load, cur_freq, max_freq, target_freq = 0;

	cur_freq = policy->cur;
	max_freq = policy->max;

	unsigned int j, avg_load;

	cpufreq_notify_utilization(policy, load);

	cur_freq = policy->cur;

	for_each_cpu(j, policy->cpus) {
		if (load > max_load_freq)
			max_load_freq = load * policy->cur;
	}
	avg_load = (ex_data.prev_load + load) >> 1;

	if (ex_tuners->gboost) {
		if (ex_data.g_count < 500 && graphics_boost < 3)
			++ex_data.g_count;
		else if (ex_data.g_count > 1)
			--ex_data.g_count;
	}

	//gboost mode
	if (ex_tuners->gboost && ex_data.g_count > 300) {
				
		if (avg_load > 40 + (graphics_boost * 10)) {
			freq_next = max_freq;
		} else {
			freq_next = max_freq * avg_load / 100;
			freq_next = MAX(freq_next, ex_tuners->gboost_min_freq);
		}

		target_freq = ex_freq_increase(policy, freq_next);

		__cpufreq_driver_target(policy, target_freq, CPUFREQ_RELATION_H);

		if (avg_load > 45 + (graphics_boost * 10)) {
			freq_next = policy->max;
		} else {
			freq_next = policy->max * avg_load / 100;
			freq_next = MAX(freq_next, ex_tuners->gboost_min_freq);
		}

		target_freq = ex_freq_increase(policy, freq_next);

		__cpufreq_driver_target(policy, target_freq, CPUFREQ_RELATION_H);

		goto finished;
	} 

	//normal mode
	if (max_load_freq > up_threshold_level[1] * cur_freq) {

		if (input_event_boosted() && FREQ_NEED_BURST(cur_freq) &&
	if (max_load_freq > up_threshold_level[1] * policy->cur) {
		if (input_event_boosted() && FREQ_NEED_BURST(policy->cur) &&
		dbs_info->down_floor = 0;
		int index = get_cpu_freq_index(cur_freq);
		int index = get_cpu_freq_index(cur_freq, dbs_data);

		if (FREQ_NEED_BURST(cur_freq) &&
				load > up_threshold_level[0]) {
			freq_next = max_freq;
		}
		
		else if (avg_load > up_threshold_level[0]) {
			freq_next = tblmap[2 + ex_tuners->powersave][index];
		}
		
		else if (avg_load <= up_threshold_level[1]) {
			freq_next = cur_freq;
			freq_next = policy->cur + 1000000;
		}
		
		else if (avg_load <= up_threshold_level[1]) {
			freq_next = cur_freq;
			freq_next = tblmap[tbl_select[1]][index];
			freq_next = tblmap1[index];
			freq_next = tblmap[0 + ex_tuners->powersave][index];
		}
	
		else {
			if (load > up_threshold_level[0]) {
				freq_next = tblmap[2 + ex_tuners->powersave][index];
			}
		
			else {
				freq_next = tblmap[1 + ex_tuners->powersave][index];
			}
		}

		target_freq = ex_freq_increase(policy, freq_next);

		__cpufreq_driver_target(policy, target_freq, CPUFREQ_RELATION_H);

				freq_next = policy->cur + 300000;
			}
		
			else {
				freq_next = cur_freq + 300000;
			}
		}

		target_freq = ex_freq_increase(policy, freq_next);

		__cpufreq_driver_target(policy, target_freq, CPUFREQ_RELATION_H);
		if (target_freq > ex_data.active_floor_freq)
			dbs_info->down_floor = 0;

		goto finished;
	}

	if (++dbs_info->down_floor > ex_tuners->sampling_down_factor)
		dbs_info->down_floor = 0;

	if (cur_freq == policy->min){
	if (policy->cur == policy->min){
	if (cur_freq == policy->min)
		goto finished;

	if (cur_freq >= ex_data.active_floor_freq) {
		if (++dbs_info->down_floor > ex_tuners->sampling_down_factor)
			dbs_info->down_floor = 0;
	} else {
		dbs_info->down_floor = 0;
	}

	if (max_load_freq <
	    (ex_tuners->up_threshold - ex_tuners->down_differential) *
	     cur_freq) {
	     policy->cur) {

		freq_next = max_load_freq /
				(ex_tuners->up_threshold -
				 ex_tuners->down_differential);

		freq_next = MAX(freq_next, policy->min);
		if (freq_next < policy->min)
			freq_next = policy->min;
		if (input_event_boosted(cpu))
			freq_next = MAX(freq_next, ex_data.input_min_freq);
		if (dbs_info->down_floor)
		if (dbs_info->down_floor && !ex_data.suspended) {
		if (dbs_info->down_floor) {
			freq_next = MAX(freq_next, ex_data.active_floor_freq);
		} else {
			freq_next = MAX(freq_next, policy->min);
			if (freq_next < ex_data.active_floor_freq)
				dbs_info->down_floor = ex_tuners->sampling_down_factor;
		}

		__cpufreq_driver_target(policy, freq_next,
			CPUFREQ_RELATION_L);
	}

finished:
	ex_data.prev_load = load;
	return;
}

static void ex_dbs_timer(struct work_struct *work)
{
	struct ex_cpu_dbs_info_s *dbs_info = container_of(work,
			struct ex_cpu_dbs_info_s, cdbs.work.work);
	unsigned int cpu = dbs_info->cdbs.cur_policy->cpu;
	struct ex_cpu_dbs_info_s *core_dbs_info = &per_cpu(ex_cpu_dbs_info,
			cpu);
	struct dbs_data *dbs_data = dbs_info->cdbs.cur_policy->governor_data;
	struct ex_dbs_tuners *ex_tuners = dbs_data->tuners;
	int delay = delay_for_sampling_rate(ex_tuners->sampling_rate);
	bool modify_all = true;

	mutex_lock(&core_dbs_info->cdbs.timer_mutex);
	if (!need_load_eval(&core_dbs_info->cdbs, ex_tuners->sampling_rate))
		modify_all = false;
	else
		dbs_check_cpu(dbs_data, cpu);

	gov_queue_work(dbs_data, dbs_info->cdbs.cur_policy, delay, modify_all);
	mutex_unlock(&core_dbs_info->cdbs.timer_mutex);
}


static void dbs_input_event_boost(int cpu)
{
	struct ex_cpu_dbs_info_s *dbs_info = &per_cpu(ex_cpu_dbs_info, cpu);

	dbs_info->input_event_boost = true;
	dbs_info->input_event_boost_expired = jiffies +
		usecs_to_jiffies(ex_data.input_event_timeout * 1000);
}

static void dbs_input_event(struct input_handle *handle, unsigned int type,
		unsigned int code, int value)
{
	int i;

	if (ex_data.suspended)
		return;

	if (ex_data.input_event_timeout == 0)
		return;

	if (type == EV_ABS && code == ABS_MT_TRACKING_ID) {
		if (value != -1) {		
			ex_data.input_event_boost = true;
			ex_data.input_event_boost_expired = jiffies +
				usecs_to_jiffies(ex_data.input_event_timeout * 1000);
			spin_lock_irqsave(&ex_data.input_boost_lock, flags);
			ex_data.input_event_boost = true;
			ex_data.input_event_boost_expired = jiffies +
				usecs_to_jiffies(ex_data.input_event_timeout * 1000);
		if (value != -1) {
			for_each_online_cpu(i)
				dbs_input_event_boost(i);
		}
	}
}

static int dbs_input_connect(struct input_handler *handler,
		struct input_dev *dev, const struct input_device_id *id)
{
	struct input_handle *handle;
	int error;

	handle = kzalloc(sizeof(struct input_handle), GFP_KERNEL);
	if (!handle)
		return -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "cpufreq";

	error = input_register_handle(handle);
	if (error)
		goto err2;

	error = input_open_device(handle);
	if (error)
		goto err1;

	return 0;

err1:
	input_unregister_handle(handle);
err2:
	kfree(handle);
	return error;
}

static void dbs_input_disconnect(struct input_handle *handle)
{
	input_close_device(handle);
	input_unregister_handle(handle);
	kfree(handle);
}

static const struct input_device_id dbs_ids[] = {
	// multi-touch touchscreen
	{
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
			INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_ABS) },
		.absbit = { [BIT_WORD(ABS_MT_POSITION_X)] =
			BIT_MASK(ABS_MT_POSITION_X) |
			BIT_MASK(ABS_MT_POSITION_Y) },
	},
	// touchpad
	{
		.flags = INPUT_DEVICE_ID_MATCH_KEYBIT |
			INPUT_DEVICE_ID_MATCH_ABSBIT,
		.keybit = { [BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH) },
		.absbit = { [BIT_WORD(ABS_X)] =
			BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) },
	},
	// Keypad
	{
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_KEY) },
	},
	{ },
};

static struct input_handler dbs_input_handler = {
	.event		= dbs_input_event,
	.connect	= dbs_input_connect,
	.disconnect	= dbs_input_disconnect,
	.name		= "cpufreq_elementalx",
	.id_table	= dbs_ids,
};

static int fb_notifier_callback(struct notifier_block *this,
				unsigned long event, void *data)
{
	struct fb_event *evdata = data;
	int *blank;

	if (evdata && evdata->data && event == FB_EVENT_BLANK) {
		blank = evdata->data;
		switch (*blank) {
			case FB_BLANK_UNBLANK:
				//display on
				ex_data.suspended = false;
				break;
			case FB_BLANK_POWERDOWN:
			case FB_BLANK_HSYNC_SUSPEND:
			case FB_BLANK_VSYNC_SUSPEND:
			case FB_BLANK_NORMAL:
				//display off
				ex_data.suspended = true;
				break;
		}
	}

	return NOTIFY_OK;
}

/************************** sysfs interface ************************/
static struct common_dbs_data ex_dbs_cdata;

static ssize_t store_sampling_rate(struct dbs_data *dbs_data, const char *buf,
		size_t count)
{
	struct ex_dbs_tuners *ex_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);

	if (ret != 1)
		return -EINVAL;

	ex_tuners->sampling_rate = max(input, dbs_data->min_sampling_rate);
	return count;
}

static ssize_t store_up_threshold(struct dbs_data *dbs_data, const char *buf,
		size_t count)
{
	struct ex_dbs_tuners *ex_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);

	if (ret != 1 || input > 100 || input <= ex_tuners->down_differential)
		return -EINVAL;

	ex_tuners->up_threshold = input;
	return count;
}

static ssize_t store_down_differential(struct dbs_data *dbs_data,
		const char *buf, size_t count)
{
	struct ex_dbs_tuners *ex_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);

	if (ret != 1 || input > 100 || input >= ex_tuners->up_threshold)
		return -EINVAL;

	ex_tuners->down_differential = input;
	return count;
}

static ssize_t store_active_floor_freq(struct dbs_data *dbs_data,
		const char *buf, size_t count)
{
	struct ex_dbs_tuners *ex_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);

	if (ret != 1)
		return -EINVAL;

	ex_tuners->active_floor_freq = input;
	ex_data.active_floor_freq = ex_tuners->active_floor_freq;
	return count;
}

static ssize_t store_sampling_down_factor(struct dbs_data *dbs_data,
		const char *buf, size_t count)
{
	struct ex_dbs_tuners *ex_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);

	if (ret != 1 || input > MAX_SAMPLING_DOWN_FACTOR || input < 0)
		return -EINVAL;

	ex_tuners->sampling_down_factor = input;
	return count;
}

static ssize_t store_powersave(struct dbs_data *dbs_data, const char *buf,
		size_t count)
{
	struct ex_dbs_tuners *ex_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);

	if (ret != 1 || input > 1)
		return -EINVAL;

	if (input == 0)
		ex_tuners->powersave = input;
	else if (input == 1)
		ex_tuners->powersave = 3;

	return count;
}

show_store_one(ex, sampling_rate);
show_store_one(ex, up_threshold);
show_store_one(ex, down_differential);
show_store_one(ex, active_floor_freq);
show_store_one(ex, sampling_down_factor);
show_store_one(ex, powersave);
declare_show_sampling_rate_min(ex);

gov_sys_pol_attr_rw(sampling_rate);
gov_sys_pol_attr_rw(up_threshold);
gov_sys_pol_attr_rw(down_differential);
gov_sys_pol_attr_rw(active_floor_freq);
gov_sys_pol_attr_rw(sampling_down_factor);
gov_sys_pol_attr_rw(powersave);
gov_sys_pol_attr_ro(sampling_rate_min);

static struct attribute *dbs_attributes_gov_sys[] = {
	&sampling_rate_min_gov_sys.attr,
	&sampling_rate_gov_sys.attr,
	&up_threshold_gov_sys.attr,
	&down_differential_gov_sys.attr,
	&active_floor_freq_gov_sys.attr,
	&sampling_down_factor_gov_sys.attr,
	&powersave_gov_sys.attr,
	NULL
};

static struct attribute_group ex_attr_group_gov_sys = {
	.attrs = dbs_attributes_gov_sys,
	.name = "elementalx",
};

static struct attribute *dbs_attributes_gov_pol[] = {
	&sampling_rate_min_gov_pol.attr,
	&sampling_rate_gov_pol.attr,
	&up_threshold_gov_pol.attr,
	&down_differential_gov_pol.attr,
	&active_floor_freq_gov_pol.attr,
	&sampling_down_factor_gov_pol.attr,
	&powersave_gov_pol.attr,
	NULL
};

static struct attribute_group ex_attr_group_gov_pol = {
	.attrs = dbs_attributes_gov_pol,
	.name = "elementalx",
};

/************************** sysfs end ************************/

static int ex_init(struct dbs_data *dbs_data, struct cpufreq_policy *policy)
{
	struct ex_dbs_tuners *tuners;

	tuners = kzalloc(sizeof(*tuners), GFP_KERNEL);
	if (!tuners) {
		pr_err("%s: kzalloc failed\n", __func__);
		return -ENOMEM;
	}

	tuners->up_threshold = DEF_FREQUENCY_UP_THRESHOLD;
	tuners->down_differential = DEF_FREQUENCY_DOWN_DIFFERENTIAL;
	tuners->ignore_nice_load = 0;
	tuners->active_floor_freq = DEF_ACTIVE_FLOOR_FREQ;
	tuners->sampling_down_factor = DEF_SAMPLING_DOWN_FACTOR;
	tuners->powersave = 0;

	dbs_data->tuners = tuners;
	dbs_data->min_sampling_rate = MIN_SAMPLING_RATE;
	dbs_data->freq_table = cpufreq_frequency_get_table(policy->cpu);

	mutex_init(&dbs_data->mutex);

	return 0;
}

static void ex_exit(struct dbs_data *dbs_data)
{
	kfree(dbs_data->tuners);
}

define_get_cpu_dbs_routines(ex_cpu_dbs_info);

static struct common_dbs_data ex_dbs_cdata = {
	.governor = GOV_ELEMENTALX,
	.attr_group_gov_sys = &ex_attr_group_gov_sys,
	.attr_group_gov_pol = &ex_attr_group_gov_pol,
	.get_cpu_cdbs = get_cpu_cdbs,
	.get_cpu_dbs_info_s = get_cpu_dbs_info_s,
	.gov_dbs_timer = ex_dbs_timer,
	.gov_check_cpu = ex_check_cpu,
	.init_ex = ex_init,
	.exit = ex_exit,
};

static int ex_cpufreq_governor_dbs(struct cpufreq_policy *policy,
				   unsigned int event)
{
	return cpufreq_governor_dbs(policy, &ex_dbs_cdata, event);
}

#ifndef CONFIG_CPU_FREQ_DEFAULT_GOV_ELEMENTALX
static
#endif
struct cpufreq_governor cpufreq_gov_elementalx = {
	.name			= "elementalx",
	.governor		= ex_cpufreq_governor_dbs,
	.max_transition_latency	= TRANSITION_LATENCY_LIMIT,
	.owner			= THIS_MODULE,
};

static int __init cpufreq_gov_dbs_init(void)
{
	return cpufreq_register_governor(&cpufreq_gov_elementalx);
}

static void __exit cpufreq_gov_dbs_exit(void)
{
	cpufreq_unregister_governor(&cpufreq_gov_elementalx);
}

MODULE_AUTHOR("Aaron Segaert <asegaert@gmail.com>");
MODULE_DESCRIPTION("'cpufreq_elementalx' - multiphase cpufreq governor");
MODULE_LICENSE("GPL");

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_ELEMENTALX
fs_initcall(cpufreq_gov_dbs_init);
#else
module_init(cpufreq_gov_dbs_init);
#endif
module_exit(cpufreq_gov_dbs_exit);
