#include "bluetooth.h"
#include "common.h"
#include "BT.h"
#include "bluetooth_gui.h"
#include "sys/app_controller.h"

#define SERVER_REFLUSH_INTERVAL 5000UL
struct BluetoothAppRunData
{
    boolean bt_start; // 标志是否开启蓝牙服务，0为关闭 1为开启
    boolean req_sent; // 标志是否发送蓝牙请求服务，0为关闭 1为开启
    unsigned long serverReflushPreMillis; // 上一回更新的时间
};

static BluetoothAppRunData *run_data = NULL;

void bluetooth_init(void)
{
    bluetooth_gui_init();

    run_data=(BluetoothAppRunData *)malloc(sizeof(BluetoothAppRunData));
    run_data->bt_start=0;
    run_data->req_sent=0;
    run_data->serverReflushPreMillis=0;
}

void bluetooth_process(AppController *sys,
                      const Imu_Action *action)
{
    lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_NONE;

    if (RETURN == action->active)
    {
        sys->app_exit();
        return;
    }
        //如果蓝牙没有打开
    if(run_data->bt_start==0 && run_data->req_sent==0){
      display_bluetooth("wait...",LV_SCR_LOAD_ANIM_NONE);
      sys->req_event(&bluetooth_app,APP_EVENT_BT,0);//req_event没有蓝牙的事件处理
      run_data->req_sent=1;
    }
    else if(run_data->bt_start==0){
      if(doDelayMillisTime(SERVER_REFLUSH_INTERVAL, &run_data->serverReflushPreMillis, false) == true){
        sys->req_event(&bluetooth_app,APP_EVENT_BT,0);

        display_bluetooth(pCharacteristic->getValue().c_str(),LV_SCR_LOAD_ANIM_NONE);
      }

    }
}

void bluetooth_exit_callback(void)
{
  bluetooth_gui_del();
  free(run_data);
  run_data=NULL;
}

void bluetooth_event_notification(APP_EVENT_TYPE type, int event_id)
{
  switch (type)
  {
    case APP_EVENT_BT:
    {
      Serial.print(F("APP_EVENT_BT enable\n"));
      display_bluetooth(pCharacteristic->getValue().c_str(),LV_SCR_LOAD_ANIM_NONE);
      
      run_data->bt_start=1;
    }
    break;
    case APP_EVENT_BT_ALIVE:
    {

    }
    default:
      break;
  }
}

APP_OBJ bluetooth_app={"bluetooth",&app_bluetooth,"",bluetooth_init,
                        bluetooth_process,bluetooth_exit_callback,
                        bluetooth_event_notification};