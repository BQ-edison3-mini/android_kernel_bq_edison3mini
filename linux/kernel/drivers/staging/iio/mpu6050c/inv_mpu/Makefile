#
# Makefile for Invensense inv-mpu-iio device.
#

obj-$(CONFIG_INV_MPU_IIO) += inv-mpu-iio.o

inv-mpu-iio-objs := inv_mpu_core.o
inv-mpu-iio-objs += inv_mpu_ring.o
inv-mpu-iio-objs += inv_mpu_trigger.o
inv-mpu-iio-objs += inv_mpu_misc.o
inv-mpu-iio-objs += inv_mpu3050_iio.o
inv-mpu-iio-objs += dmpDefaultMPU6050.o

#--yd CFLAGS_inv_mpu_core.o      += -Idrivers/staging/iio
#--yd CFLAGS_inv_mpu_ring.o      += -Idrivers/staging/iio
#--yd CFLAGS_inv_mpu_trigger.o   += -Idrivers/staging/iio
#--yd CFLAGS_inv_mpu_misc.o      += -Idrivers/staging/iio
#--yd CFLAGS_inv_mpu3050_iio.o   += -Idrivers/staging/iio
#--yd CFLAGS_dmpDefaultMPU6050.o += -Idrivers/staging/iio
CFLAGS_inv_mpu_core.o      += -Idrivers/iio -Iinclude/linux/iio -Idrivers/iio/imu
CFLAGS_inv_mpu_ring.o      += -Idrivers/iio -Iinclude/linux/iio -Idrivers/iio/imu
CFLAGS_inv_mpu_trigger.o   += -Idrivers/iio -Iinclude/linux/iio -Idrivers/iio/imu
CFLAGS_inv_mpu_misc.o      += -Idrivers/iio -Iinclude/linux/iio -Idrivers/iio/imu
CFLAGS_inv_mpu3050_iio.o   += -Idrivers/iio -Iinclude/linux/iio -Idrivers/iio/imu
CFLAGS_dmpDefaultMPU6050.o += -Idrivers/iio -Iinclude/linux/iio -Idrivers/iio/imu

# the Bosch BMA250 driver is added to the inv-mpu device driver because it
# must be connected to an MPU3050 device on the secondary slave bus.
ifeq ($(CONFIG_INV_IIO_MPU3050_ACCEL_SLAVE_BMA250), y)
inv-mpu-iio-objs += inv_slave_bma250.o
CFLAGS_inv_slave_bma250.o   += -Idrivers/staging/iio
endif

