#include <linux/cdev.h>
#include <linux/debugfs.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

#define MSG_SIZE 7
#define BUF_SIZE 255
#define FILE_NAME "test"
#define DIRECTORY_NAME "traineeTest"
#define MSG " World\n"

static size_t file_length= 0;
static char foo_buf[BUF_SIZE];
static struct dentry *dir = NULL;
static struct dentry *testFile = NULL;

struct file_data {
    struct cdev cdev;
};

static ssize_t file_read(struct file *file, char __user *buf, size_t count,
            loff_t *f_pos)
{
	return simple_read_from_buffer(buf, count, f_pos, foo_buf, BUF_SIZE);
}

static ssize_t file_write(struct file *file, const char __user *buf, size_t count,
                    loff_t *f_pos)
{
	size_t ret;
	int tmp = 0;
	char* msg_pointer = MSG;

	if (*f_pos > BUF_SIZE)
		return -EINVAL;

	ret = simple_write_to_buffer(foo_buf + file_length, BUF_SIZE, f_pos, buf, count);

	if (ret < 0)
		return ret;

	ret -= 1;
	tmp = MSG_SIZE + ret;

	while (ret < tmp) {
		*(foo_buf + ret++) = *msg_pointer++;
	}

	*(foo_buf + ret) = '\0';
	return ret;
}

static int file_open(struct inode *inode, struct file *filep)
{
	struct file_data *my_data;
	my_data = container_of(inode->i_cdev, struct file_data, cdev);
	filep->private_data = my_data;
	return 0;
}

static const struct file_operations file_fops = {
	.owner = THIS_MODULE,
	.open = file_open,
	.read = file_read,
	.write = file_write,
};

void create_file(void)
{
	dir = debugfs_lookup(DIRECTORY_NAME, NULL);

	if (!dir) {
		dir = debugfs_create_dir(DIRECTORY_NAME, NULL);

		if (!dir) {
			printk(KERN_ALERT "MessageModule: failed to create"
				" /sys/kernel/debug/traineeTest\n");
			return;
		}
	}

	testFile = debugfs_lookup(FILE_NAME, dir);

	if (!testFile) {
		testFile = debugfs_create_file(FILE_NAME, 0666, dir,
		 "", &file_fops);

		if (!testFile) {
			printk(KERN_ALERT "MessageModule: failed to create"
				" /sys/kernel/debug/traineeTest/test\n");
			return;
		}
	}

	return;
}

void delete_file(void)
{
	debugfs_remove_recursive(dir);
}

static int __init msg_init(void)
{
	create_file();
	return 0;
}

static void __exit msg_exit(void)
{
	delete_file();
}

module_init(msg_init);
module_exit(msg_exit);
