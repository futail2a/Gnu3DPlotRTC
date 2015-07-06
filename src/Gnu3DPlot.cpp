// -*- C++ -*-
/*!
 * @file  Gnu3DPlot.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "Gnu3DPlot.h"
#define GNUPLOT_PATH "C:\PROGRA~2/gnuplot/bin/pgnuplot.exe" 

// Module specification
// <rtc-template block="module_spec">
static const char* gnu3dplot_spec[] =
  {
    "implementation_id", "Gnu3DPlot",
    "type_name",         "Gnu3DPlot",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Gnu3DPlot::Gnu3DPlot(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_pointIn("point", m_point)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Gnu3DPlot::~Gnu3DPlot()
{
}



RTC::ReturnCode_t Gnu3DPlot::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("point", m_pointIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Gnu3DPlot::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Gnu3DPlot::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Gnu3DPlot::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Gnu3DPlot::onActivated(RTC::UniqueId ec_id)
{
	m_gp = _popen(GNUPLOT_PATH, "w"); // パイプを開き、gnuplotの立ち上げ
	if (m_gp == NULL){
		return RTC::RTC_ERROR;
	}
	//have to add config
	fprintf(m_gp, "set xrange [-3:3]\n");	// 範囲の指定
	fprintf(m_gp, "set yrange [-3:3]\n");
	fprintf(m_gp, "set zrange [-10:10]\n");
	fprintf(m_gp, "set xlabel \"x\"\n");	// ラベル表示
	fprintf(m_gp, "set ylabel \"y\"\n");
	fprintf(m_gp, "set zlabel \"z\"\n");

	return RTC::RTC_OK;
}



RTC::ReturnCode_t Gnu3DPlot::onDeactivated(RTC::UniqueId ec_id)
{
	fprintf(m_gp, "exit\n"); // gnuplotの終了
	fflush(m_gp);
	_pclose(m_gp); // パイプを閉じる
  return RTC::RTC_OK;
}



RTC::ReturnCode_t Gnu3DPlot::onExecute(RTC::UniqueId ec_id)
{
	if (m_pointIn.isNew()){
		m_pointIn.read();
		fprintf(m_gp, "splot '-' with points pointtype 6 pointsize 5\n");
		fprintf(m_gp, "%f\t%f\t%f\n", m_point.data.position.x, m_point.data.position.z, m_point.data.position.y);
		fprintf(m_gp, "e\n");
	}

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Gnu3DPlot::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Gnu3DPlot::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Gnu3DPlot::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Gnu3DPlot::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Gnu3DPlot::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void Gnu3DPlotInit(RTC::Manager* manager)
  {
    coil::Properties profile(gnu3dplot_spec);
    manager->registerFactory(profile,
                             RTC::Create<Gnu3DPlot>,
                             RTC::Delete<Gnu3DPlot>);
  }
  
};


