import { query } from '$app/server';
import * as fs from 'fs'

export const getDir = query(async () => {
    return fs.readdirSync('/home/michael')
})