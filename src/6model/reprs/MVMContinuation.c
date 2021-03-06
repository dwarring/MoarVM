#include "moar.h"

/* This representation's function pointer table. */
static const MVMREPROps this_repr;

/* Creates a new type object of this representation, and associates it with
 * the given HOW. Also sets the invocation protocol handler in the STable. */
static MVMObject * type_object_for(MVMThreadContext *tc, MVMObject *HOW) {
    MVMSTable *st = MVM_gc_allocate_stable(tc, &this_repr, HOW);

    MVMROOT(tc, st, {
        MVMObject *obj = MVM_gc_allocate_type_object(tc, st);
        MVM_ASSIGN_REF(tc, &(st->header), st->WHAT, obj);
        st->size = sizeof(MVMContinuation);
    });

    return st->WHAT;
}

/* Creates a new instance based on the type object. */
static MVMObject * allocate(MVMThreadContext *tc, MVMSTable *st) {
    return MVM_gc_allocate_object(tc, st);
}

/* Copies the body of one object to another. */
static void copy_to(MVMThreadContext *tc, MVMSTable *st, void *src, MVMObject *dest_root, void *dest) {
    MVMContinuationBody *src_body  = (MVMContinuationBody *)src;
    MVMContinuationBody *dest_body = (MVMContinuationBody *)dest;
    MVM_panic(MVM_exitcode_NYI, "MVMContinuation copy_to NYI");
}

/* Adds held objects to the GC worklist. */
static void gc_mark(MVMThreadContext *tc, MVMSTable *st, void *data, MVMGCWorklist *worklist) {
    MVMContinuationBody *body = (MVMContinuationBody *)data;
    MVM_gc_worklist_add_frame(tc, worklist, body->top);
    MVM_gc_worklist_add_frame(tc, worklist, body->root);
    if (body->active_handlers) {
        MVMActiveHandler *cur_ah = body->active_handlers;
        while (cur_ah != NULL) {
            MVM_gc_worklist_add(tc, worklist, &cur_ah->ex_obj);
            cur_ah = cur_ah->next_handler;
        }
    }
}

/* Called by the VM in order to free memory associated with this object. */
static void gc_free(MVMThreadContext *tc, MVMObject *obj) {
    MVMContinuation *ctx = (MVMContinuation *)obj;
    if (ctx->body.top)
        ctx->body.top = MVM_frame_dec_ref(tc, ctx->body.top);
    if (ctx->body.root)
        ctx->body.root = MVM_frame_dec_ref(tc, ctx->body.root);
    if (ctx->body.active_handlers) {
        MVMActiveHandler *cur_ah = ctx->body.active_handlers;
        while (cur_ah != NULL) {
            MVMActiveHandler *next_ah = cur_ah->next_handler;
            MVM_frame_dec_ref(tc, cur_ah->frame);
            free(cur_ah);
            cur_ah = next_ah;
        }
    }
}

/* Gets the storage specification for this representation. */
static MVMStorageSpec get_storage_spec(MVMThreadContext *tc, MVMSTable *st) {
    MVMStorageSpec spec;
    spec.inlineable      = MVM_STORAGE_SPEC_REFERENCE;
    spec.boxed_primitive = MVM_STORAGE_SPEC_BP_NONE;
    spec.can_box         = 0;
    return spec;
}

/* Compose the representation. */
static void compose(MVMThreadContext *tc, MVMSTable *st, MVMObject *info) {
    /* Nothing to do for this REPR. */
}

/* Initializes the representation. */
const MVMREPROps * MVMContinuation_initialize(MVMThreadContext *tc) {
    return &this_repr;
}

static const MVMREPROps this_repr = {
    type_object_for,
    allocate,
    NULL, /* initialize */
    copy_to,
    MVM_REPR_DEFAULT_ATTR_FUNCS,
    MVM_REPR_DEFAULT_BOX_FUNCS,
    MVM_REPR_DEFAULT_POS_FUNCS,
    MVM_REPR_DEFAULT_ASS_FUNCS,
    NULL, /* elems */
    get_storage_spec,
    NULL, /* change_type */
    NULL, /* serialize */
    NULL, /* deserialize */
    NULL, /* serialize_repr_data */
    NULL, /* deserialize_repr_data */
    NULL, /* deserialize_stable_size */
    gc_mark,
    gc_free,
    NULL, /* gc_cleanup */
    NULL, /* gc_mark_repr_data */
    NULL, /* gc_free_repr_data */
    compose,
    "MVMContinuation", /* name */
    MVM_REPR_ID_MVMContinuation,
    1, /* refs_frames */
};
