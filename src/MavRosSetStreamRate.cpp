/* 
 * @File:     MavRosSetStreamRate.cpp
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#include "MavRosSetStreamRate.h"

MavRosSetStreamRate::MavRosSetStreamRate()
{
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<mavros_msgs::StreamRate>("/mavros/set_stream_rate");
  mavros_msgs::StreamRate srv;
  srv.request.stream_id = 0;
  srv.request.message_rate = 100;
  srv.request.on_off = 1;

  if (client.call(srv))
  {
    ROS_INFO("Send OK");
  }
  else
  {
    ROS_INFO("Failed to call service");
  }

  ros::ServiceClient cl_get = n.serviceClient<mavros_msgs::ParamGet>("/mavros/param/get");
  mavros_msgs::ParamGet paramget;
  paramget.request.param_id = "SYSID_MYGCS";

  if (cl_get.call(paramget))
  {
    ROS_INFO("Send OK %d Value: %ld", paramget.response.success, paramget.response.value.integer);
    SYSID_MYGCS_Value = paramget.response.value.integer;
  }

  paramget.request.param_id = "ARMING_CHECK";

  if (cl_get.call(paramget))
  {
    ROS_INFO("Send OK %d Value: %ld", paramget.response.success, paramget.response.value.integer);
    ARMING_CHECK_Value = paramget.response.value.integer;
  }

  paramget.request.param_id = "FS_GCS_ENABLE";

  if (cl_get.call(paramget))
  {
    ROS_INFO("Send OK %d Value: %ld", paramget.response.success, paramget.response.value.integer);
    FS_GCS_ENABLE_Value = paramget.response.value.integer;
  }

}
