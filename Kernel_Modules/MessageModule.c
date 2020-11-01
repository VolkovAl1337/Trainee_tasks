#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fcntl.h>

MODULE_LICENSE("GPL");

#define MSG_SIZE 7
#define BUF_SIZE 255
#define FILE_NAME "test.txt"
#define DIRECTORY_NAME "traineeTest"
#define MSG " World\n"

static char foo_buf[BUF_SIZE];
static struct dentry *dir = 0;
static struct dentry *testFile = 0;

static ssize_t file_read(struct file *file, char __user *buf, size_t count,
            loff_t *f_pos)
{
	return simple_read_from_buffer(buf, count, f_pos, foo_buf, sizeof(foo_buf));
}

static ssize_t file_write(struct file *file, const char __user *buf, size_t count,
                    loff_t *f_pos)
{
	size_t ret;
	int tmp = 0;

	if (*f_pos > BUF_SIZE)
		return -EINVAL;

	ret = simple_write_to_buffer(foo_buf, sizeof(foo_buf), f_pos, buf, count);

	if (ret < 0)
		return ret;

	--ret;

	while (tmp < MSG_SIZE) {
		foo_buf[ret + tmp] = MSG[tmp];
		++tmp;
	}

	ret += tmp;
	foo_buf[ret] = '\0';

	return ret;
}

static const struct file_operations file_fops = {
	.owner = THIS_MODULE,
	.read = file_read,
	.write = file_write,
};

int create_file(void)
{
	dir = debugfs_lookup(DIRECTORY_NAME, 0);

	if (!dir) {
		dir = debugfs_create_dir(DIRECTORY_NAME, 0);

		if (!dir) {
			printk(KERN_ALERT "MessageModule: failed to create"
				" /sys/kernel/debug/traineeTest\n");
			return -1;
		}
	}
	testFile = debugfs_lookup(FILE_NAME, dir);
	if(!testFile) {
		testFile = debugfs_create_file(FILE_NAME, 0777, dir,
		 "", &file_fops);

		if (!testFile) {
			printk(KERN_ALERT "MessageModule: failed to create"
				" /sys/kernel/debug/traineeTest/test.txt\n");
			return -1;
		}
	}

	return 0;
}

void delete_file(void)
{
	debugfs_remove(testFile);
	debugfs_remove_recursive(dir);
}


static int msg_init(void)
{
	create_file();
	return 0;
}
static void msg_exit(void)
{
	delete_file();
}
module_init(msg_init);
module_exit(msg_exit);
