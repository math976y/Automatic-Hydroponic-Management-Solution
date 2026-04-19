import EventEmitter, { on } from 'node:events';
import { publicProcedure, router } from './trpc';
import z from 'zod';

export type PhVal = { pH: number };
export type HumidifierVal = { temperature: number, humidity: number }
export type ECVal = { EC: number }
const ee = new EventEmitter();

let lastPhVal: PhVal|undefined;
let lastHumidifierVal: HumidifierVal|undefined;
let lastECVal: ECVal|undefined;
let lastPumpVal: boolean = false;
let lastHumiditySetPoint: number = 60;

export const appRouter = router({
    setPump: publicProcedure
        .input(z.boolean())
        .query((opts) => {
            console.log('Pump state: ', opts.input)
            lastPumpVal = opts.input;
            ee.emit('pump', lastPumpVal);
        }),
    setPhVal: publicProcedure
        .input(z.number())
        .query((opts) => {
            lastPhVal = {pH: opts.input};
            ee.emit('ph', lastPhVal)
        }),
    setHumidifierVal: publicProcedure
        .input(z.object({humidity: z.number(), temperature: z.number()}))
        .query((opts) => {
            lastHumidifierVal = opts.input;
            ee.emit('humidifier', lastHumidifierVal);
        }),
    setECVal: publicProcedure
        .input(z.number())
        .query((opts) => {
            lastECVal = {EC: opts.input};
            ee.emit('ec', lastECVal);
        }),
    setHumiditySetPoint: publicProcedure
        .input(z.number())
        .query((opts) => {
            lastHumiditySetPoint = opts.input;
            ee.emit('humiditySetPoint', lastHumiditySetPoint);
        }),
    
    onPumpVal: publicProcedure.subscription(async function* (opts) {
        if (lastPumpVal) yield lastPumpVal;
        for await (const [data] of on(ee, 'pump', {signal: opts.signal})) {
            const post = data as boolean;
            yield post;
        }
    }),
    onPhVal: publicProcedure.subscription(async function* (opts) {
        if (lastPhVal) yield lastPhVal;
        for await (const [data] of on(ee, 'ph', {signal: opts.signal})) {
            const post = data as PhVal;
            yield post;
        }
    }),
    onHumidifierVal: publicProcedure.subscription(async function* (opts) {
        if (lastHumidifierVal) yield lastHumidifierVal;
        for await (const [data] of on(ee, 'humidifier', {signal: opts.signal})) {
            const post = data as HumidifierVal;
            yield post;
        }
    }),
    onECVal: publicProcedure.subscription(async function* (opts) {
        if (lastECVal) yield lastECVal;
        for await (const [data] of on(ee, 'ec', {signal: opts.signal})) {
            const post = data as ECVal;
            yield post;
        }
    }),
    onHumiditySetPoint: publicProcedure.subscription(async function* (opts) {
        if (lastHumiditySetPoint) yield lastHumiditySetPoint;
        for await (const [data] of on(ee, 'humiditySetPoint', {signal: opts.signal})) {
            const post = data as number;
            yield post;
        }
    }),
});



// Export only the type of a router!
// This prevents us from importing server code on the client.
export type AppRouter = typeof appRouter;