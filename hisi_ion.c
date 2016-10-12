/*
 * hisi_ion.c
 *
 * Reversed ION functions compatible with Hisilicon Kirin SoCs
 *
 *   Copyright 2016 Eduardo Alonso <edu@error404software.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#define LOG_TAG "Hisi_ION"

#include <cutils/log.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <linux/ion.h>
#include <ion/ion.h>
#include <ion/hisi_ion.h>

int ion_map_iommu(int fd, unsigned int handle,
		struct iommu_map_format format)
{
	struct ion_map_iommu_data data;
	data.handle = handle;
	data.format = format;

	int ret = ioctl(fd, ION_IOC_MAP_IOMMU, &data);
	
	if (ret)
	    ALOGE("ION_MAP_IOMMU: Failed with code:%d %s\n", ret, strerror(errno));

	return ret;
}

int ion_unmap_iommu(int fd, unsigned int handle,
		    struct iommu_map_format format)
{
	struct ion_map_iommu_data data;
	data.handle = handle;
	data.format = format;

	int ret = ioctl(fd, ION_IOC_UNMAP_IOMMU, &data);

	if (ret)
	    ALOGE("ION_UNMAP_IOMMU: Failed with code:%d %s\n", ret, strerror(errno));

	return ret;
}

int ion_invalidate_fd(int fd, unsigned int handle)
{
	struct ion_fd_data data;
	data.fd = handle;

	int ret = ioctl(fd, ION_IOC_INV, &data);

	if (ret)
	    ALOGE("ION_INVALIDATE_FD: Failed with code: %d %s\n", ret, strerror(errno));

	return ret;
}
//TODO: Complete ion_get_phys
int ion_get_phys(int fd, int handle, struct ion_phys_data phys_data)
{
	struct ion_custom_data data;
	//struct io
	int asd = handle;
	
//	data.cmd = ION_HISI_CUSTOM_PHYS;
	data.arg = (unsigned long) &phys_data;

	int ret = ioctl(fd, ION_IOC_CUSTOM, &data);
	
	return ret;
}
