

struct vnode *kio_open(const char * file, int flags, int cmode);

void kio_close(struct vnode *vp);

int kio_write(struct vnode *vp, void *buf, size_t size);




