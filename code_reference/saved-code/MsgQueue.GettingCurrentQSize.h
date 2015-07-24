// ---------------------------------------------------------------------------

template <typename MSG> bool MsgQueue<MSG>::AddMsg(
    unsigned char *buffer,
    unsigned int   len,
    EWN_IP        *srcAddr,
    EWN_IP        *dstAddr,
    unsigned int   clientMask,
    unsigned int   serverMask)
{
    unsigned int next_idx;

    synch_MutexLock_Quiet(m_lock);
    next_idx = (m_input_idx + 1) % MAX_QUEUE_SIZE;

    if(m_qfull) {
        synch_MutexUnlock_Quiet(m_lock);
        MAND_LOG(DBG_INFO, "MsgQueue::AddMsg - Overflow, qsize=%d", MAX_QUEUE_SIZE);
        return false;
    } else  if(next_idx == m_output_idx) {
        // next_idx == m_output_idx could mean both queue empty and queue full
        // the m_qfull flag serves to differentiate the two cases
        m_qfull = true;
    }

    uint qs;

    if (m_output_idx > next_idx) {
        qs = m_output_idx - next_idx;
    } else if (m_qfull){
        qs =0;
    } else {
        qs = MAX_QUEUE_SIZE - next_idx + m_output_idx;
    }
    MAND_LOG(DBG_INFO, "AddMsg: next_idx=%d, m_output_idx=%d, queue_sz=%d", next_idx, m_output_idx, qs);


    if(!OnCopy(&(m_queue[next_idx]), buffer, len,
           srcAddr, dstAddr,
           clientMask, serverMask))
    {
        synch_MutexUnlock_Quiet(m_lock);
        MAND_LOG(DBG_INFO, "MsgQueue::AddMsg - OnCopy failed, msg size=%d", len);
        return false;
    }
    m_input_idx = next_idx;

    // Unblock the reader
    synch_SemaphorePost(m_semReader);

    synch_MutexUnlock_Quiet(m_lock);

#ifdef EWN_REPLAY
    replay_DoWait();
#endif // EWN_REPLAY

    return true;
}

// ---------------------------------------------------------------------------

template <typename MSG> MSG *MsgQueue<MSG>::GetNextMsg() {
    MSG *retval;
    do {
        synch_MutexLock_Quiet(m_lock);
        if(m_input_idx == m_output_idx) {
            synch_MutexUnlock_Quiet(m_lock);

            // No message, wait for a writer to insert a message
            synch_SemaphoreWait(m_semReader);
            pthread_testcancel();
        } else {
            // A message has arrived, return it
            break;
        }
    } while(true);

    m_output_idx = (m_output_idx + 1) % MAX_QUEUE_SIZE;
    retval = &m_queue[m_output_idx];
    m_qfull = false;
    synch_MutexUnlock_Quiet(m_lock);

    uint qs;
    if (m_output_idx > m_input_idx) {
        qs = m_output_idx - m_input_idx;
    } else {
        qs = MAX_QUEUE_SIZE - m_input_idx + m_output_idx;
    }
    MAND_LOG(DBG_INFO, "GetMsg: m_input_idx=%d, m_output_idx=%d, queue_sz=%d", m_input_idx, m_output_idx, qs);


    return retval;
}
