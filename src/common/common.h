#ifndef WATER_COMMON_H
#define WATER_COMMON_H

#define WaterInterface struct

#define SAFE_DELETE(ptr) if(ptr != nullptr) delete ptr;
#define SAFE_DELETE_ARRAY(ptr) if (ptr != nullptr) delete[] ptr;

#define	DECL_SHARED_PTR(cls) typedef std::shared_ptr<cls> cls##Ptr;
#define DECL_WEEK_PTR(cls) typedef std::weak_ptr<cls> cls##WeekPtr;

#define WATER_ID unsigned long

namespace water {

	WaterInterface IPlugin{
		virtual void on_init() = 0;
		virtual void on_frame() = 0;
		virtual void on_destroy() = 0;
	};

}

#endif